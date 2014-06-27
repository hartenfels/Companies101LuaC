#ifndef COMPANIES101_EQUAL_H
#define COMPANIES101_EQUAL_H
#include "c101_Company.h"
#include "c101_Subunit.h"
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

bool c101_equalCompany   (struct c101_Company   * lhs, struct c101_Company   * rhs);

bool c101_equalSubunit   (struct c101_Subunit   * lhs, struct c101_Subunit   * rhs);

bool c101_equalDepartment(struct c101_Department* lhs, struct c101_Department* rhs);

bool c101_equalEmployee  (struct c101_Employee  * lhs, struct c101_Employee  * rhs);

#ifdef __cplusplus
}
#endif
#endif

