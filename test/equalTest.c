#include "c101_Test.h"
#include "c101_Equal.h"

C101_TEST_BEGIN()
    struct c101_Company* other = c101_makeSampleCompany();

    C101_TEST_ASSERT(c101_equalCompany(c101_sampleCompany, c101_sampleCompany))
    C101_TEST_ASSERT(c101_equalCompany(other, other))
    C101_TEST_ASSERT(c101_equalCompany(c101_sampleCompany, other))

    other->name[0] = 'I';
    C101_TEST_ASSERT( c101_equalCompany(other, other))
    C101_TEST_ASSERT(!c101_equalCompany(c101_sampleCompany, other))

    c101_freeCompany(other);
C101_TEST_END()

