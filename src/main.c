#include "c101_Cut.h"
#include "c101_Company.h"
#include "c101_Depth.h"
#include "c101_Equal.h"
#include "c101_Median.h"
#include "c101_Parsing.h"
#include "c101_Print.h"
#include "c101_Subunit.h"
#include "c101_Total.h"
#include "c101_Unparsing.h"
#include <assert.h>
#include <stdio.h>

int
main(void)
{
    struct c101_Company* c1 =
            c101_newCompany("Acme Corporation", 2,
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
    c101_print(c1);
    printf("Depth:  %u\n", c101_depth (c1));
    printf("Median: %g\n", c101_median(c1));
	printf("Total:  %g\n", c101_total (c1));
	c101_cut(c1);
	printf("Cut:    %g\n", c101_total (c1));

    assert(c101_equalCompany(c1, c1));

    struct c101_Company* c2 = c101_parse("sample.lua");
    assert(c101_equalCompany(c1, c2));

    FILE* luaOut  = fopen("out.lua",  "w");
    if (!luaOut) {
        perror("Could not write to out.lua");
        return EXIT_FAILURE;
    }

    FILE* jsonOut = fopen("out.json", "w");
    if (!jsonOut) {
        perror("Could not write to out.json");
        return EXIT_FAILURE;
    }

    c101_unparse(c1, luaOut, jsonOut);

    fclose(jsonOut);
    fclose(luaOut );
    c101_freeCompany(c2);
    c101_freeCompany(c1);
    return 0;
}

