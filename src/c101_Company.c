#include "c101_Company.h"
#include "c101_Subunit.h"
#include "c101_Util.h"
#include <assert.h>
#include <stdarg.h>

struct c101_Company*
c101_newCompany(const char* n, size_t count, ...)
{
    struct c101_Company* c = c101_malloc(sizeof(struct c101_Company));
    c->name                = c101_strdup(n);
    if (count) {
        c->subunits = c101_newVector(count, c101_freeSubunit);
        va_list vl;
        va_start(vl, count);
        while (count--)
            c101_pushBack(&c->subunits, va_arg(vl, struct c101_Subunit*));
    } else
        c->subunits = c101_newVector(1, c101_freeSubunit);
    return c;
}

void c101_freeCompany(struct c101_Company* c)
{
    free(c->name);
    c101_freeVector(&c->subunits);
    free(c);
}


void
c101_setCompanyName(struct c101_Company* c, const char* n)
{
    free(c->name);
    c->name = c101_strdup(n);
}

void c101_addDepartment (struct c101_Company* c, struct c101_Subunit* d)
{
    assert(d->isDepartment);
    c101_pushBack(&c->subunits, d);
}

