#include <stdio.h>
#include <stdlib.h>

#include "plural.h"

int main()
{
    plural_t * first_pl =  plural_new();
    plural_t * second_pl =  plural_new();


    plural_add_element(3, first_pl);
    plural_add_interval(7,15,first_pl);
    printf("First:            ");
    plural_pf(first_pl);
    printf("\nPower first: %i\n", plural_power(first_pl));
    plural_delete_element(9,first_pl);
    printf("First:            ");
    plural_pf(first_pl);
    printf("\nPower first: %i\n", plural_power(first_pl));

    plural_delete_interval(11,13,first_pl);
    printf("First:            ");
    plural_pf(first_pl);
    printf("\nPower first: %i\n", plural_power(first_pl));

    puts("\n");

    plural_add_element(2, second_pl);
    plural_add_interval(13,17,second_pl);
    plural_add_interval(20,23,second_pl);
    printf("Second:           ");
    plural_pf(second_pl);
    printf("\nPower second: %i\n", plural_power(second_pl));

    puts("\n");

    printf("\nDifference:       ");
    plural_difference(first_pl, second_pl);

    printf("\nAssociation:      ");
    plural_association(first_pl, second_pl);

    printf("\nSymmetric Diff:   ");
    plural_symmetric_difference(first_pl, second_pl);

    plural_free(first_pl);
    plural_free(second_pl);

    puts("\n");

    return 0;
}
