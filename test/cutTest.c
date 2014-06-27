#include "c101_Test.h"
#include "c101_Cut.h"
#include "c101_Total.h"

C101_TEST_BEGIN()
    c101_cut(c101_sampleCompany);
    C101_TEST_ASSERT(c101_approxEq(c101_total(c101_sampleCompany), C101_SAMPLE_CUT, 0.1))
C101_TEST_END()

