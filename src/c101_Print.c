#include "c101_Print.h"
#include "c101_Subunit.h"
#include "c101_Visit.h"
#include <stdio.h>

static int
printVisitor(enum c101_VisitorType type, void* unit, void* userData)
{
    double* depth = userData;
    switch (type) {
    case C101_COMPANY:
        {
            struct c101_Company* c = unit;
            printf("%s (%zd Departments)\n", c->name, c->subunits.size);
        }
        ++*depth;
        break;

    case C101_COMPANY_END:
        --*depth;
        break;

    case C101_DEPARTMENT:
        for (size_t i = 0; i < *depth; ++i)
            putchar('\t');
        {
            struct c101_Department* d = unit;
            printf("%s (%zd Subunits)\n", d->name, d->subunits.size);
        }
        ++*depth;
        break;

    case C101_DEPARTMENT_END:
        --*depth;
        break;

    case C101_EMPLOYEE:
        for (size_t i = 0; i < *depth; ++i)
            putchar('\t');
        {
            struct c101_Employee* e = unit;
            printf("%s, %s, %g\n", e->name, e->address, e->salary);
        }
        break;

    default:
        break;
    }
    return 0;
}

void
c101_print(struct c101_Company* c)
{
    size_t depth = 0;
    c101_visitCompany(c, &depth, printVisitor);
}

