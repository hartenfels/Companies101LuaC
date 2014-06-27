#include "c101_Test.h"
#include "c101_Equal.h"
#include "c101_Parsing.h"

C101_TEST_BEGIN()
    struct c101_Company* parsed = c101_parse("sample.lua");
    C101_TEST_ASSERT(parsed)
    C101_TEST_ASSERT(c101_equalCompany(c101_sampleCompany, parsed))
C101_TEST_END()

