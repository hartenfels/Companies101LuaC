#include "c101_Depth.h"
#include "c101_Subunit.h"
#include "c101_Visit.h"

static int
depthVisitor(enum c101_VisitorType type, void* unit, void* userData)
{
    (void) unit;
    unsigned int* depths = userData;
    switch (type) {
    case C101_DEPARTMENT:
        if (depths[1] < ++depths[0])
            depths[1] = depths[0];
        break;

    case C101_DEPARTMENT_END:
        --depths[0];
        break;

    default:
        break;
    }
    return 0;
}

unsigned int
c101_depth(struct c101_Company* c)
{
    // depths[0] is current depth, depths[1] is maximum depth
    unsigned int depths[2] = {0, 0};
    c101_visitCompany(c, &depths, depthVisitor);
    return depths[1];
}

