#include "c101_Parsing.h"
#include "c101_Company.h"
#include "c101_Subunit.h"
#include "c101_Util.h"
#include "c101_Vector.h"
#include <setjmp.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

struct ParseData {
    struct c101_Company* company;
    struct c101_Vector   stack;
};

static void
parseError(lua_State* lua, struct ParseData* data, jmp_buf* env)
{
    fputs(lua_tostring(lua, -1), stderr);
    lua_close(lua);
    if (data) {
        if (data->company)
            c101_freeCompany(data->company);
        if (data->stack.capacity)
            c101_freeVector (&data->stack);
    }
    longjmp(*env, 1);
}

static int
c101_parseCompany(lua_State* lua)
{
    struct ParseData* data = lua_touserdata (lua, 1);
    const char      * name = lua_tostring   (lua, 2);

    data->company = c101_newCompany(name, 0);
    data->stack   = c101_newVector (1, NULL);

    return 0;
}

static int
c101_parseDepartment(lua_State* lua)
{
    struct ParseData* data = lua_touserdata (lua, 1);
    const char      * name = lua_tostring   (lua, 2);

    struct c101_Subunit* subunit = c101_newDepartment(name, 0);
    if (data->stack.size)
        c101_addSubunit   (c101_back(&data->stack), subunit);
    else
        c101_addDepartment(data->company, subunit);
    c101_pushBack(&data->stack, subunit);

    return 0;
}

static int
c101_parseEmployee(lua_State* lua)
{
    struct ParseData* data    = lua_touserdata (lua, 1);
    const char      * name    = lua_tostring   (lua, 2);
    const char      * address = lua_tostring   (lua, 3);
    double            salary  = lua_tonumber   (lua, 4);

    c101_addSubunit(c101_back(&data->stack), c101_newEmployee(name, address, salary));

    return 0;
}

static int
c101_endDepartment(lua_State* lua)
{
    struct ParseData* data = lua_touserdata(lua, 1);
    c101_popBack(&data->stack);
    return 0;
}

struct c101_Company*
c101_parse(const char* file)
{
    jmp_buf env;
    if (setjmp(env))
        return NULL;

    lua_State* lua = luaL_newstate();
    if (!lua)
        c101_error(1, "Could not create Lua state", &env);
    luaL_openlibs(lua);
    if (luaL_dofile(lua, "parsing.lua"))
        parseError(lua, NULL, &env);

    lua_pushcfunction(lua,  c101_parseCompany    );
    lua_setglobal    (lua, "c101_parseCompany"   );
    lua_pushcfunction(lua,  c101_parseDepartment );
    lua_setglobal    (lua, "c101_parseDepartment");
    lua_pushcfunction(lua,  c101_parseEmployee   );
    lua_setglobal    (lua, "c101_parseEmployee"  );
    lua_pushcfunction(lua,  c101_endDepartment   );
    lua_setglobal    (lua, "c101_endDepartment"  );

    lua_getglobal(lua, "parseCompany");
    struct ParseData data = {0};
    lua_pushlightuserdata(lua, &data);

    if (luaL_dofile(lua, file))
        parseError(lua, &data, &env);

    if (lua_pcall(lua, 2, 0, 0))
        parseError(lua, &data, &env);
    lua_close(lua);

    c101_freeVector(&data.stack);
	return data.company;
}

