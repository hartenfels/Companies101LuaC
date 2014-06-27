#include "c101_Util.h"
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void*
c101_malloc(size_t size)
{
    void* mem = malloc(size);
    if (!mem)
        exit(COMPANIES101_ERROR_MALLOC);
    return mem;
}

void*
c101_calloc(size_t num, size_t size)
{
    void* mem = calloc(num, size);
    if (!mem)
        exit(COMPANIES101_ERROR_CALLOC);
    return mem;
}

void*
c101_realloc(void* ptr, size_t size)
{
    void* mem = realloc(ptr, size);
    if (!mem)
        exit(COMPANIES101_ERROR_REALLOC);
    return mem;
}

char*
c101_strdup(const char* str)
{
    size_t len = strlen(str);
    if (len) {
        char* buf = c101_malloc(len + 1);
        strcpy(buf, str);
        return buf;
    }
    return NULL;
}

int
c101_error(int err, const char* msg, jmp_buf* env)
{
    fprintf(stderr, "%s (Code %d)\n", msg, err);
    if (env)
        longjmp(*env, err);
    return err;
}

