#ifndef COMPANIES101_TEST_H
#define COMPANIES101_TEST_H
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

#define C101_SAMPLE_CUT    199873.5
#define C101_SAMPLE_DEPTH  3
#define C101_SAMPLE_MEDIAN 57106.7
#define C101_SAMPLE_TOTAL  399747.0

#define C101_TEST_BEGIN()   int main(void) { if (c101_initTest()) return 255;
#define C101_TEST_END()     c101_exitTest(); return 0; }
#define C101_TEST_FAIL()    { c101_exitTest(); return 1; }
#define C101_TEST_SUCCEED() { c101_exitTest(); return 0; }
#define C101_TEST_ASSERT(x) { if (!(x)) { return 1; } }
#define C101_TEST_JUST(x) C101_TEST_BEGIN() C101_TEST_ASSERT(x) C101_TEST_END()

extern struct c101_Company* c101_sampleCompany;

int  c101_initTest(void);

void c101_exitTest(void);

bool c101_approxEq(double actual, double expected, double delta);

struct c101_Company* c101_makeSampleCompany();

#ifdef __cplusplus
}
#endif
#endif

