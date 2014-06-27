#include "c101_Visit.h"
#include <setjmp.h>

struct VisitorData {
    int   (* visitor)(enum c101_VisitorType, void*, void*);
    void   * userData;
    jmp_buf* env;
};

static void
c101_visitSubunit(void* v, void* d)
{
    struct c101_Subunit* su   = v;
    struct VisitorData * data = d;

    int err;
    if (su->isDepartment) {
        if ((err = c101_visitDepartment(&su->department, data->userData, data->visitor)))
            longjmp(*data->env, err);
    } else {
        if ((err = c101_visitEmployee  (&su->employee  , data->userData, data->visitor)))
            longjmp(*data->env, err);
    }
}

int
c101_visitCompany(struct c101_Company* c, void* userData,
                  int (*visitor)(enum c101_VisitorType, void*, void*))
{
    int err;
    if ((err = visitor(C101_COMPANY,     c, userData)))
        return err;

    jmp_buf env;
    if ((err = setjmp(env)))
        return err;

    struct VisitorData data = {visitor, userData, &env};
    c101_fold(c101_begin(&c->subunits), c101_end(&c->subunits), &data, c101_visitSubunit);

    return visitor(C101_COMPANY_END, c, userData);
}

int
c101_visitDepartment(struct c101_Department* d, void* userData,
                     int (*visitor)(enum c101_VisitorType, void*, void*))
{
    int err;
    if ((err = visitor(C101_DEPARTMENT,     d, userData)))
        return err;

    jmp_buf env;
    if ((err = setjmp(env)))
        return err;

    struct VisitorData data = {visitor, userData, &env};
    c101_fold(c101_begin(&d->subunits), c101_end(&d->subunits), &data, c101_visitSubunit);

    return visitor(C101_DEPARTMENT_END, d, userData);
}

int
c101_visitEmployee(struct c101_Employee* employee, void* userData,
                   int (*visitor)(enum c101_VisitorType, void*, void*))
{ return visitor(C101_EMPLOYEE, employee, userData); }

