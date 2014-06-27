#include "c101_Subunit.h"
#include "c101_Util.h"
#include <assert.h>
#include <stdarg.h>

struct c101_Subunit*
c101_newEmployee(const char* n, const char* a, double s)
{
    struct c101_Subunit* e = c101_malloc(sizeof(struct c101_Subunit));
    e->isDepartment        = false;
    e->employee.name       = c101_strdup(n);
    e->employee.address    = c101_strdup(a);
    e->employee.salary     = s;
    return e;
}


struct c101_Employee*
c101_toEmployee(struct c101_Subunit* su)
{ return su->isDepartment ? NULL : &su->employee; }


void
c101_setEmployeeName(struct c101_Subunit* e, const char* n)
{
    assert(!e->isDepartment);
    free(e->employee.name);
    e->employee.name = c101_strdup(n);
}

void
c101_setEmployeeAddress(struct c101_Subunit* e, const char* a)
{
    assert(!e->isDepartment);
    free(e->employee.address);
    e->employee.address = c101_strdup(a);
}

void
c101_setEmployeeSalary(struct c101_Subunit* e, double s)
{
    assert(!e->isDepartment);
    e->employee.salary = s;
}


struct c101_Subunit*
c101_newDepartment(const char* n, size_t count, ...)
{
    struct c101_Subunit* d = c101_malloc(sizeof(struct c101_Subunit));
    d->isDepartment        = true;
    d->department.name     = c101_strdup(n);

    if (count) {
        d->department.subunits = c101_newVector(count, c101_freeSubunit);
        va_list vl;
        va_start(vl, count);
        while (count--)
            c101_pushBack(&d->department.subunits, va_arg(vl, struct c101_Subunit*));
    } else
        d->department.subunits = c101_newVector(1, c101_freeSubunit);

    return d;
}

struct c101_Department*
c101_toDepartment(struct c101_Subunit* su)
{ return su->isDepartment ? &su->department : NULL; }


void
c101_setDepartmentName(struct c101_Subunit* d, const char* n)
{
    assert(d->isDepartment);
    free(d->department.name);
    d->department.name = c101_strdup(n);
}

void
c101_addSubunit(struct c101_Subunit* d, struct c101_Subunit* su)
{
    assert(d->isDepartment);
    c101_pushBack(&d->department.subunits, su);
}


void
c101_freeSubunit(void* v)
{
    struct c101_Subunit* su = v;
    if (su->isDepartment) {
        free(su->department.name);
        c101_freeVector(&su->department.subunits);
    } else {
        free(su->employee.name);
        free(su->employee.address);
    }
    free(su);
}

