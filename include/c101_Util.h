#ifndef COMPANIES101_UTIL_HPP
#define COMPANIES101_UTIL_HPP
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
struct lua_State;

/**<!--===============================================================================-->

@file c101_Util.h Utility functions.


Feature
=======

Memory allocation via malloc/calloc/realloc can sometimes fail, but this contribution
can't handle those errors appropriately. This class contains simple wrappers that exit
the program with an appropriate exit status if one of those calls fails.

There is also a custom strdup function similar to the strdup function provided, to keep
the program compliant to the ISO C standard.

<!--================================================================================-->*/


/** <!---------------------------------------------------------------------------------->
Error codes for this contribution.
The error codes are bit flags that could potentially be ORed together, but as of now none
of the functions does so.
<!------------------------------------------------------------------------------------>*/
enum c101_Errors {
    COMPANIES101_ERROR_MALLOC  = 1 << 0,
    COMPANIES101_ERROR_CALLOC  = 1 << 1,
    COMPANIES101_ERROR_REALLOC = 1 << 2,
};


/** <!---------------------------------------------------------------------------------->
Wrapper for `malloc` that exits the program if `NULL` was returned.
@return Always a valid pointer to the allocated memory, there is no need to check it
again.
<!------------------------------------------------------------------------------------>*/
void* c101_malloc (size_t size);


/** <!---------------------------------------------------------------------------------->
Wrapper for `calloc` that exits the program if `NULL` was returned.
@return Always a valid pointer to the allocated memory, there is no need to check it
again.
<!------------------------------------------------------------------------------------>*/
void* c101_calloc (size_t num,
                   size_t size);


/** <!---------------------------------------------------------------------------------->
Wrapper for `realloc` that exits the program if `NULL` was returned.
@return Always a valid pointer to the allocated memory, there is no need to check it
again.
<!------------------------------------------------------------------------------------>*/
void* c101_realloc(void*  ptr,
                   size_t size);


/** <!---------------------------------------------------------------------------------->
Copies the given string into newly allocated memory that can later be `free`d.
If allocation fails, the program will exit, as per ::c101_malloc.
@param str A null-terminated string or even just `NULL`.
@return A pointer to the allocated memory containing a copy of str or `NULL` if a string
of length 0 or `NULL` was given.
@see c101_malloc
<!------------------------------------------------------------------------------------>*/
char* c101_strdup  (const char* str);


int   c101_error(int         err,
                 const char* msg,
                 jmp_buf   * env);


#ifdef __cplusplus
}
#endif
#endif

