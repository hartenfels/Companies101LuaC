#include "c101_Cut.h"
#include "c101_Visit.h"

static int
cutVisitor(enum c101_VisitorType type, void* unit, void* userData)
{
    (void) userData;
    if (type == C101_EMPLOYEE)
        ((struct c101_Employee*) unit)->salary /= 2.0;
    return 0;
}

void
c101_cut(struct c101_Company* c)
{ c101_visitCompany(c, NULL, cutVisitor); }

