#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "plural.h"

static void new_void_zeroCount(void **state)
{
    plural_t * plural = plural_new();
    assert_int_equal(plural_power(plural), 0);
    plural_free(plural);
}

static void add_oneValue_countOne(void **state)
{
    plural_t * plural = plural_new();
    plural_add_element(13, plural);
    assert_int_equal(plural_power(plural), 1);
    plural_free(plural);
}

static void add_twoValues_countTwo(void **state)
{
    plural_t * plural = plural_new();
    plural_add_element(13, plural);
    plural_add_element(9, plural);
    assert_int_equal(plural_power(plural), 2);
    plural_free(plural);
}

static void addIinterval_intervalValues_numberOfNumbersInInterval(void **state)
{
    plural_t * plural = plural_new();
    plural_add_interval(9, 13, plural);
    assert_int_equal(plural_power(plural), 5);
    plural_free(plural);
}

static void delete_oneValue_zeroCount(void **state)
{
    plural_t * plural = plural_new();

    plural_add_element(13, plural);
    plural_delete_element(13, plural);
    assert_int_equal(plural_power(plural), 0);

    plural_free(plural);
}

static void deleteInterval_intervalValues_zeroCount(void **state)
{
    plural_t * plural = plural_new();

    plural_add_interval(9, 13, plural);
    plural_delete_interval(9, 13, plural);
    assert_int_equal(plural_power(plural), 0);

    plural_free(plural);
}

static void difference_firstAndSecondAndResultPlural_countOne(void **state)
{
    plural_t * first_plural = plural_new();
    plural_t * second_plural = plural_new();
    plural_t * result = plural_new();

    plural_add_interval(9, 13, first_plural);
    plural_add_interval(10, 13, second_plural);

    result = plural_difference(first_plural, second_plural, result);
    assert_int_equal(plural_power(result), 1);

    plural_free(first_plural);
    plural_free(second_plural);
    plural_free(result);
}

static void association_firstAndSecondAndResultPlural_countNineteen(void **state)
{
    plural_t * first_plural = plural_new();
    plural_t * second_plural = plural_new();
    plural_t * result = plural_new();

    plural_add_interval(1, 10, first_plural);
    plural_add_interval(10, 19, second_plural);

    result = plural_association(first_plural, second_plural, result);
    assert_int_equal(plural_power(result), 19);

    plural_free(first_plural);
    plural_free(second_plural);
    plural_free(result);
}

static void symmetricDifference_firstAndSecondAndResultPlural_countFourteen(void **state)
{
    plural_t * first_plural = plural_new();
    plural_t * second_plural = plural_new();
    plural_t * result = plural_new();

    plural_add_interval(9, 15, first_plural);
    plural_add_interval(13, 25, second_plural);

    result = plural_symmetric_difference(first_plural, second_plural, result);
    assert_int_equal(plural_power(result), 14);

    plural_free(first_plural);
    plural_free(second_plural);
    plural_free(result);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zeroCount),
        cmocka_unit_test(add_oneValue_countOne),
        cmocka_unit_test(add_twoValues_countTwo),
        cmocka_unit_test(addIinterval_intervalValues_numberOfNumbersInInterval),
        cmocka_unit_test(delete_oneValue_zeroCount),
        cmocka_unit_test(deleteInterval_intervalValues_zeroCount),
        cmocka_unit_test(difference_firstAndSecondAndResultPlural_countOne),
        cmocka_unit_test(association_firstAndSecondAndResultPlural_countNineteen),
        cmocka_unit_test(symmetricDifference_firstAndSecondAndResultPlural_countFourteen),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
