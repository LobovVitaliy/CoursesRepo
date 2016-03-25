#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "heap.h"

static void heap_new__void__zeroCount_zeroSize(void **state)
{
    heap_t * heap = heap_new();

    assert_int_equal(heap_count(heap), 0);
    assert_int_equal(heap_size(heap), 0);

    heap_free(heap);
}

static void memory_new__heap_index_size__zeroCount_thirtyFiveSize(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 35);

            assert_int_equal(memory_count(heap, 0), 0);
            assert_int_equal(memory_size(heap, 0), 35);

            assert_int_equal(heap_count(heap), 0);
            assert_int_equal(heap_size(heap), 35);

        heap_memory_clear(heap, 0);
    heap_free(heap);
}



static void memory_set__heap_index_offset_string_length__fourCount_twentySize(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);

            memory_set(heap, 0, 4, "Programme", 4);

            assert_int_equal(memory_count(heap, 0), 4);
            assert_int_equal(memory_size(heap, 0), 20);

            assert_int_equal(heap_count(heap), 4);
            assert_int_equal(heap_size(heap), 20);

        heap_memory_clear(heap, 0);
    heap_free(heap);
}

static void memory_set__heap_index_offset_string_length__eightCount_twentySize(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);

            memory_set(heap, 0, 4, "Holidays", 4);
            memory_set(heap, 0, 1, "Holidays", 4);

            assert_int_equal(memory_count(heap, 0), 8);
            assert_int_equal(memory_size(heap, 0), 20);

            assert_int_equal(heap_count(heap), 8);
            assert_int_equal(heap_size(heap), 20);

        heap_memory_clear(heap, 0);
    heap_free(heap);
}

static void memory_set__heap_index_offset_string_length__seventeenCount_twentySize(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);

            memory_set(heap, 0, 4, "Holidays", 4);
            memory_set(heap, 0, 1, "Programme", 9);
            memory_set(heap, 0, 1, "Holidays", 4);

            assert_int_equal(memory_count(heap, 0), 17);
            assert_int_equal(memory_size(heap, 0), 20);

            assert_int_equal(heap_count(heap), 17);
            assert_int_equal(heap_size(heap), 20);

        heap_memory_clear(heap, 0);
    heap_free(heap);
}



static void memory_get__heap_index_offset_string_length__firstString(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);

            memory_set(heap, 0, 4, "Programme", 4);
            assert_string_equal(memory_get(heap, 0, 1, 4), "gram");

        heap_memory_clear(heap, 0);
    heap_free(heap);
}

static void memory_get__heap_index_offset_string_length__secondString(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);

            memory_set(heap, 0, 1, "Testing", 7);
            memory_set(heap, 0, 4, "Programme", 4);
            assert_string_equal(memory_get(heap, 0, 1, 11), "Testinggram");

        heap_memory_clear(heap, 0);
    heap_free(heap);
}

static void memory_get__heap_index_offset_string_length__thirdString(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);

            memory_set(heap, 0, 1, "Testing", 7);
            memory_set(heap, 0, 1, "Holidays", 4);
            memory_set(heap, 0, 4, "Programme", 4);

            assert_string_equal(memory_get(heap, 0, 1, 15), "TestingHoligram");

        heap_memory_clear(heap, 0);
    heap_free(heap);
}



static void memory_set__heap_index_offset_string_length__fourAndEightCount_twentyAndFortySize(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);
        heap = heap_memory_allocate(heap, 1, 20);

            memory_set(heap, 0, 4, "Programme", 4);
            memory_set(heap, 1, 1, "Holidays", 8);

            assert_int_equal(memory_count(heap, 0), 4);
            assert_int_equal(memory_size(heap, 0), 20);
            assert_int_equal(memory_count(heap, 1), 8);
            assert_int_equal(memory_size(heap, 1), 20);

            assert_int_equal(heap_count(heap), 12);
            assert_int_equal(heap_size(heap), 40);

        heap_memory_clear(heap, 0);
        heap_memory_clear(heap, 1);
    heap_free(heap);
}

static void memory_set__heap_index_offset_string_length__fourAndEightAndFourCountAndSixteen_twentyAndTwentyFiveAndThirtySizeAndSeventyFive(void **state)
{
    heap_t * heap = heap_new();
        heap = heap_memory_allocate(heap, 0, 20);
        heap = heap_memory_allocate(heap, 2, 30);
        heap = heap_memory_allocate(heap, 1, 25);

            memory_set(heap, 0, 4, "Programme", 4);
            memory_set(heap, 2, 1, "Testing", 4);
            memory_set(heap, 1, 1, "Holidays", 8);

            assert_int_equal(memory_count(heap, 0), 4);
            assert_int_equal(memory_size(heap, 0), 20);
            assert_int_equal(memory_count(heap, 1), 8);
            assert_int_equal(memory_size(heap, 1), 25);
            assert_int_equal(memory_count(heap, 2), 4);
            assert_int_equal(memory_size(heap, 2), 30);

            assert_int_equal(heap_count(heap), 16);
            assert_int_equal(heap_size(heap), 75);

        heap_memory_clear(heap, 0);
        heap_memory_clear(heap, 1);
        heap_memory_clear(heap, 2);
    heap_free(heap);
}



int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(heap_new__void__zeroCount_zeroSize),
        cmocka_unit_test(memory_new__heap_index_size__zeroCount_thirtyFiveSize),

        cmocka_unit_test(memory_set__heap_index_offset_string_length__fourCount_twentySize),
        cmocka_unit_test(memory_set__heap_index_offset_string_length__eightCount_twentySize),
        cmocka_unit_test(memory_set__heap_index_offset_string_length__seventeenCount_twentySize),

        cmocka_unit_test(memory_get__heap_index_offset_string_length__firstString),
        cmocka_unit_test(memory_get__heap_index_offset_string_length__secondString),
        cmocka_unit_test(memory_get__heap_index_offset_string_length__thirdString),

        cmocka_unit_test(memory_set__heap_index_offset_string_length__fourAndEightCount_twentyAndFortySize),
        cmocka_unit_test(memory_set__heap_index_offset_string_length__fourAndEightAndFourCountAndSixteen_twentyAndTwentyFiveAndThirtySizeAndSeventyFive)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
