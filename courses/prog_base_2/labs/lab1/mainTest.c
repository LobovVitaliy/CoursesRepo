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

static void memory_new__heap_size__zeroCount_thirtyFiveSize(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 35);

            assert_int_equal(memory_count(mem), 0);
            assert_int_equal(memory_size(mem), 35);

            assert_int_equal(heap_count(heap), 0);
            assert_int_equal(heap_size(heap), 35);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}



static void memory_set__memory_offset_string_length__fourCount_twentySize(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);

            assert_int_equal(memory_count(mem), 4);
            assert_int_equal(memory_size(mem), 20);

            assert_int_equal(heap_count(heap), 4);
            assert_int_equal(heap_size(heap), 20);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_set__memory_offset_string_length__eightCount_twentySize(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Holidays", 4);
            memory_set(mem, 1, "Holidays", 4);

            assert_int_equal(memory_count(mem), 8);
            assert_int_equal(memory_size(mem), 20);

            assert_int_equal(heap_count(heap), 8);
            assert_int_equal(heap_size(heap), 20);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_set__memory_offset_string_length__seventeenCount_twentySize(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Holidays", 4);
            memory_set(mem, 1, "Programme", 9);
            memory_set(mem, 1, "Holidays", 4);

            assert_int_equal(memory_count(mem), 17);
            assert_int_equal(memory_size(mem), 20);

            assert_int_equal(heap_count(heap), 17);
            assert_int_equal(heap_size(heap), 20);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}



static void memory_get__memory_offset_string_length__firstString(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            assert_string_equal(memory_get(mem, 1, 4), "gram");

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_string_length__secondString(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 1, "Testing", 7);
            memory_set(mem, 4, "Programme", 4);
            assert_string_equal(memory_get(mem, 1, 11), "Testinggram");

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_string_length__thirdString(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 1, "Testing", 7);
            memory_set(mem, 1, "Holidays", 4);
            memory_set(mem, 4, "Programme", 4);

            assert_string_equal(memory_get(mem, 1, 15), "TestingHoligram");

        heap_memory_clear(heap, mem);
    heap_free(heap);
}



static void memory_set__memory_offset_string_length__fourAndEightCount_twentyAndFortySize(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem1 = heap_memory_allocate(heap, 20);
        memory_t * mem2 = heap_memory_allocate(heap, 20);

            memory_set(mem1, 4, "Programme", 4);
            memory_set(mem2, 1, "Holidays", 8);

            assert_int_equal(memory_count(mem1), 4);
            assert_int_equal(memory_size(mem1), 20);
            assert_int_equal(memory_count(mem2), 8);
            assert_int_equal(memory_size(mem2), 20);

            assert_int_equal(heap_count(heap), 12);
            assert_int_equal(heap_size(heap), 40);

        heap_memory_clear(heap, mem1);
        heap_memory_clear(heap, mem2);
    heap_free(heap);
}

static void memory_set__memory_offset_string_length__fourAndEightAndFourCountAndSixteen_twentyAndTwentyFiveAndThirtySizeAndSeventyFive(void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem1 = heap_memory_allocate(heap, 20);
        memory_t * mem2 = heap_memory_allocate(heap, 30);
        memory_t * mem3 = heap_memory_allocate(heap, 25);

            memory_set(mem1, 4, "Programme", 4);
            memory_set(mem2, 1, "Testing", 4);
            memory_set(mem3, 1, "Holidays", 8);

            assert_int_equal(memory_count(mem1), 4);
            assert_int_equal(memory_size(mem1), 20);
            assert_int_equal(memory_count(mem2), 4);
            assert_int_equal(memory_size(mem2), 30);
            assert_int_equal(memory_count(mem3), 8);
            assert_int_equal(memory_size(mem3), 25);

            assert_int_equal(heap_count(heap), 16);
            assert_int_equal(heap_size(heap), 75);

        heap_memory_clear(heap, mem1);
        heap_memory_clear(heap, mem2);
        heap_memory_clear(heap, mem3);
    heap_free(heap);
}



int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(heap_new__void__zeroCount_zeroSize),
        cmocka_unit_test(memory_new__heap_size__zeroCount_thirtyFiveSize),

        cmocka_unit_test(memory_set__memory_offset_string_length__fourCount_twentySize),
        cmocka_unit_test(memory_set__memory_offset_string_length__eightCount_twentySize),
        cmocka_unit_test(memory_set__memory_offset_string_length__seventeenCount_twentySize),

        cmocka_unit_test(memory_get__memory_offset_string_length__firstString),
        cmocka_unit_test(memory_get__memory_offset_string_length__secondString),
        cmocka_unit_test(memory_get__memory_offset_string_length__thirdString),

        cmocka_unit_test(memory_set__memory_offset_string_length__fourAndEightCount_twentyAndFortySize),
        cmocka_unit_test(memory_set__memory_offset_string_length__fourAndEightAndFourCountAndSixteen_twentyAndTwentyFiveAndThirtySizeAndSeventyFive)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

