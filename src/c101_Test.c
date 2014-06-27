#include "c101_Test.h"
#include "c101_Company.h"
#include "c101_Subunit.h"
#include "math.h"

struct c101_Company* c101_sampleCompany;

int
c101_initTest(void)
{ return (c101_sampleCompany = c101_makeSampleCompany()) == NULL; }

void
c101_exitTest(void)
{
    if (c101_sampleCompany)
        c101_freeCompany(c101_sampleCompany);
}

bool
c101_approxEq(double actual, double expected, double delta)
{ return fabs(actual - expected) < delta; }

struct c101_Company*
c101_makeSampleCompany()
{
	return c101_newCompany("Acme Corporation", 2,
               c101_newDepartment("Research", 3,
                   c101_newEmployee("Craig", "Redmond", 123456),
                   c101_newEmployee("Erik" , "Utrecht", 12345 ),
                   c101_newEmployee("Ralf" , "Koblenz", 1234  )
               ),
               c101_newDepartment("Development", 2,
                   c101_newEmployee  ("Ray", "Redmond", 234567),
                   c101_newDepartment("Dev1", 2,
                       c101_newEmployee  ("Klaus", "Boston", 23456),
                       c101_newDepartment("Dev1.1", 2,
                           c101_newEmployee("Karl", "Riga"     , 2345),
                           c101_newEmployee("Joe" , "Wifi City", 2344)
                       )
                   )
               )
           );
}

