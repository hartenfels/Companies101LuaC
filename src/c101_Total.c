#include "c101_Total.h"
#include "c101_Subunit.h"
#include "c101_Visit.h"

static int
totalVisitor(enum c101_VisitorType type, void* unit, void* out)
{
    if (type == C101_EMPLOYEE)
        *(double*) out += ((struct c101_Employee*) unit)->salary;
    return 0;
}

double
c101_total(struct c101_Company* c)
{
    double out = 0.0;
    c101_visitCompany(c, &out, totalVisitor);
    return out;
}

