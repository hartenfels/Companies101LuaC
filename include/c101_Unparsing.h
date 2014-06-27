#ifndef COMPANIES101_UNPARSING_H
#define COMPANIES101_UNPARSING_H
#include "c101_Company.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

int c101_unparse(struct c101_Company* company, FILE* luaOut, FILE* jsonOut);

#ifdef __cplusplus
}
#endif
#endif

