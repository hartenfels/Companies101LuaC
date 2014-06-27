#include "c101_Parsing.h"
#include "c101_Subunit.h"
#include "c101_Util.h"
#include "c101_Visit.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int
unparseError(lua_State* lua)
{
    fputs(lua_tostring(lua, -1), stderr);
    lua_close(lua);
    return 2;
}

static void
luaSwap(lua_State* lua)
{
    lua_pushvalue(lua, -2);
    lua_pushvalue(lua, -2);
    lua_replace  (lua, -4);
    lua_replace  (lua, -2);
}

static int
unparseVisitor(enum c101_VisitorType type, void* unit, void* data)
{
    lua_State* lua = data;

    switch (type) {
    case C101_COMPANY:
        lua_getglobal (lua, "unparseCompany");
        lua_pushstring(lua, ((struct c101_Company*) unit)->name);
        if (lua_pcall(lua, 1, 1, 0))
            return unparseError(lua);
        break;

    case C101_DEPARTMENT:
        lua_getglobal (lua, "unparseDepartment");
        luaSwap       (lua);
        lua_pushstring(lua, ((struct c101_Department*) unit)->name);
        if (lua_pcall(lua, 2, 2, 0))
            return unparseError(lua);
        break;

    case C101_DEPARTMENT_END:
        lua_pop(lua, 1);
        break;

    case C101_EMPLOYEE:
        lua_getglobal(lua, "unparseEmployee");
        luaSwap      (lua);
        {
            struct c101_Employee* e = unit;
            lua_pushstring(lua, e->name);
            lua_pushstring(lua, e->address);
            lua_pushnumber(lua, e->salary);
        }
        if (lua_pcall(lua, 4, 1, 0))
            return unparseError(lua);
        break;

    default:
        break;
    }

    return 0;
}

static int
luaWrite(lua_State* lua, const char* func, FILE* out)
{
    lua_getglobal(lua, func);
    luaSwap      (lua);
    if (lua_pcall(lua, 1, 2, 0))
        return unparseError(lua);

    errno = 0;
    if (fputs(lua_tostring(lua, -1), out) == EOF)
        perror("Could not write unparsing result");

    lua_pop(lua, 1);
    return errno;
}

int
c101_unparse(struct c101_Company* c, FILE* luaOut, FILE* jsonOut)
{
    lua_State* lua = luaL_newstate();
    if (!lua)
        return c101_error(1, "Could not create Lua state", NULL);
    luaL_openlibs(lua);
    if (luaL_dofile(lua, "unparsing.lua"))
        return unparseError(lua);

    int err  = 0;
    if ((err = c101_visitCompany(c, lua, unparseVisitor)))
        return err;

    if (luaOut && luaWrite(lua, "dumpLua",  luaOut ))
        err = -1;
    if (luaOut && luaWrite(lua, "dumpJson", jsonOut))
        err -= 2;

    lua_close(lua);
    return err;
}

