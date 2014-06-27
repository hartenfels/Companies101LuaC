#include "c101_Equal.h"
#include <string.h>
#include <stdio.h>

bool
c101_equalCompany(struct c101_Company* lhs, struct c101_Company* rhs)
{
    if (strcmp(lhs->name, rhs->name) || lhs->subunits.size != rhs->subunits.size)
        return false;

    void **end = c101_end(&lhs->subunits);
    for (void **lit = c101_begin(&lhs->subunits), **rit = c101_begin(&rhs->subunits);
                lit != end;
              ++lit, ++rit)
        if (!c101_equalSubunit(*lit, *rit))
            return false;

    return true;
}

bool
c101_equalSubunit(struct c101_Subunit* lhs, struct c101_Subunit* rhs)
{
    if (lhs->isDepartment != rhs->isDepartment)
        return false;

    return lhs->isDepartment
         ? c101_equalDepartment(&lhs->department, &rhs->department)
         : c101_equalEmployee  (&lhs->employee,   &lhs->employee  );
}

bool
c101_equalDepartment(struct c101_Department* lhs, struct c101_Department* rhs)
{
    if (strcmp(lhs->name, rhs->name) || lhs->subunits.size != rhs->subunits.size)
        return false;

    void **end = c101_end(&lhs->subunits);
    for (void **lit = c101_begin(&lhs->subunits), **rit = c101_begin(&rhs->subunits);
                lit != end;
              ++lit, ++rit)
        if (!c101_equalSubunit(*lit, *rit))
            return false;

    return true;
}

bool
c101_equalEmployee(struct c101_Employee* lhs, struct c101_Employee* rhs)
{
    return !strcmp(lhs->name, rhs->name)
        && !strcmp(lhs->address, rhs->address)
        && lhs->salary == rhs->salary;
}

