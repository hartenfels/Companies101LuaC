#include "c101_Median.h"
#include "c101_Subunit.h"
#include "c101_Visit.h"

static int
medianVisitor(enum c101_VisitorType type, void* unit, void* userData)
{
    if (type == C101_EMPLOYEE) {
        double* data = userData;
        data[0] += ((struct c101_Employee*) unit)->salary;
        ++data[1];
    }
    return 0;
}

double
c101_median(struct c101_Company* c)
{
    double data[] = {0.0, 0.0};
    c101_visitCompany(c, &data, medianVisitor);
    return data[1] ? data[0] / data[1] : 0.0;
}

