#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "heap.h"


static void heap_new__void__status_ok (void **state)
{
    heap_t * heap = heap_new();
        assert_int_equal(heap_status(heap), HEAP_OK);
    heap_free(heap);
}

static void memory_new__heap_size__status_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            assert_int_equal(memory_status(mem), MEMORY_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_new__heap_size__status_no_ok (void **state)
{
    heap_t * heap = NULL;
    memory_t * mem = heap_memory_allocate(heap, 20);
    assert_int_equal(memory_status(mem), MEMORY_NO_OK);
}

static void memory_size__memory__twentySize (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            assert_int_equal(memory_size(mem), 20);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_count__memory__zeroCount (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            assert_int_equal(memory_count(mem), 0);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_size__memory__negativeSize (void **state)
{
    heap_t * heap = heap_new();
    memory_t * mem = NULL;
    assert_int_equal(memory_size(mem), -1);
    heap_free(heap);
}

static void memory_count__memory__negativeCount (void **state)
{
    heap_t * heap = heap_new();
    memory_t * mem = NULL;
    assert_int_equal(memory_count(mem), -1);
    heap_free(heap);
}

static void memory_set__memory_offset_string_length__status_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            assert_int_equal(memory_status(mem), MEMORY_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_set__memory_offset_string_length__fourCount (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            assert_int_equal(memory_count(mem), 4);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_set__memory_offset_string_length__negativeCount (void **state)
{
    heap_t * heap = heap_new();
    memory_t * mem = NULL;
    memory_set(mem, 4, "Programme", 4);
    assert_int_equal(memory_count(mem), -1);
    heap_free(heap);
}

static void memory_set__memory_negativeOffset_string_length__status_no_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, -1, "Programme", 4);
            assert_int_equal(memory_status(mem), MEMORY_NO_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_set__memory_offset_stringNull_length__status_no_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, NULL, 4);
            assert_int_equal(memory_status(mem), MEMORY_NO_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_set__memory_offset_string_negativeLength__status_no_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", -5);
            assert_int_equal(memory_status(mem), MEMORY_NO_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_set__memory_offset_string_lengthOverflow__status_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 100);
            assert_int_equal(memory_status(mem), MEMORY_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_length__string (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            assert_string_equal(memory_get(mem, 1, 4), "gram");

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_length__status_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            char * string = memory_get(mem, 1, 4);
            assert_int_equal(memory_status(mem), MEMORY_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_length__null (void **state)
{
    heap_t * heap = heap_new();
    memory_t * mem = NULL;
    memory_set(mem, 4, "Programme", 4);
    assert_int_equal(memory_get(mem, 1, 4), NULL);
    heap_free(heap);
}

static void memory_get__memory_negativeOffset_length__status_no_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            char * string = memory_get(mem, -2, 4);
            assert_int_equal(memory_status(mem), MEMORY_NO_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_negativeLength__status_no_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            char * string = memory_get(mem, 1, -10);
            assert_int_equal(memory_status(mem), MEMORY_NO_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_lengthOverflow__string (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            assert_string_equal(memory_get(mem, 1, 100), "gram________________");

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_get__memory_offset_lengthOverflow__status_ok (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Programme", 4);
            char * string = memory_get(mem, 1, 100);
            assert_int_equal(memory_status(mem), MEMORY_OK);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_count__memory__seventeenCount (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Holidays", 4);
            memory_set(mem, 1, "Programme", 9);
            memory_set(mem, 1, "Holidays", 4);
            assert_int_equal(memory_count(mem), 17);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void memory_count__memory__eightCount (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem = heap_memory_allocate(heap, 20);

            memory_set(mem, 4, "Holidays", 4);
            memory_set(NULL, 1, "Programme", 9);
            memory_set(mem, 1, "Holidays", 4);
            assert_int_equal(memory_count(mem), 8);

        heap_memory_clear(heap, mem);
    heap_free(heap);
}

static void heap_count__heap__twelveCount (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem1 = heap_memory_allocate(heap, 20);
        memory_t * mem2 = heap_memory_allocate(heap, 30);

            memory_set(mem1, 4, "Programme", 4);
            memory_set(mem2, 1, "Holidays", 8);
            assert_int_equal(heap_count(heap), 12);

        heap_memory_clear(heap, mem1);
        heap_memory_clear(heap, mem2);
    heap_free(heap);
}

static void heap_count__heap__eightCount (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem1 = heap_memory_allocate(heap, 20);
        memory_t * mem2 = heap_memory_allocate(heap, 30);

            memory_set(NULL, 4, "Programme", 4);
            memory_set(mem2, 1, "Holidays", 8);
            assert_int_equal(heap_count(heap), 8);

        heap_memory_clear(heap, mem1);
        heap_memory_clear(heap, mem2);
    heap_free(heap);
}

static void heap_size__heap__fiftySize (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem1 = heap_memory_allocate(heap, 20);
        memory_t * mem2 = heap_memory_allocate(heap, 30);

            assert_int_equal(heap_size(heap), 50);

        heap_memory_clear(heap, mem1);
        heap_memory_clear(heap, mem2);
    heap_free(heap);
}

static void heap_size__heap__twentySize (void **state)
{
    heap_t * heap = heap_new();
        memory_t * mem1 = heap_memory_allocate(heap, 20);
        memory_t * mem2 = heap_memory_allocate(NULL, 30);

            assert_int_equal(heap_size(heap), 20);

        heap_memory_clear(heap, mem1);
        heap_memory_clear(heap, mem2);
    heap_free(heap);
}


int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(heap_new__void__status_ok),
        cmocka_unit_test(memory_new__heap_size__status_ok),
        cmocka_unit_test(memory_new__heap_size__status_no_ok),
        cmocka_unit_test(memory_size__memory__twentySize),
        cmocka_unit_test(memory_count__memory__zeroCount),
        cmocka_unit_test(memory_size__memory__negativeSize),
        cmocka_unit_test(memory_count__memory__negativeCount),
        cmocka_unit_test(memory_set__memory_offset_string_length__status_ok),
        cmocka_unit_test(memory_set__memory_offset_string_length__fourCount),
        cmocka_unit_test(memory_set__memory_offset_string_length__negativeCount),
        cmocka_unit_test(memory_set__memory_negativeOffset_string_length__status_no_ok),
        cmocka_unit_test(memory_set__memory_offset_stringNull_length__status_no_ok),
        cmocka_unit_test(memory_set__memory_offset_string_negativeLength__status_no_ok),
        cmocka_unit_test(memory_set__memory_offset_string_lengthOverflow__status_ok),
        cmocka_unit_test(memory_get__memory_offset_length__string),
        cmocka_unit_test(memory_get__memory_offset_length__status_ok),
        cmocka_unit_test(memory_get__memory_offset_length__null),
        cmocka_unit_test(memory_get__memory_negativeOffset_length__status_no_ok),
        cmocka_unit_test(memory_get__memory_offset_negativeLength__status_no_ok),
        cmocka_unit_test(memory_get__memory_offset_lengthOverflow__string),
        cmocka_unit_test(memory_get__memory_offset_lengthOverflow__status_ok),
        cmocka_unit_test(memory_count__memory__seventeenCount),
        cmocka_unit_test(memory_count__memory__eightCount),
        cmocka_unit_test(heap_count__heap__twelveCount),
        cmocka_unit_test(heap_count__heap__eightCount),
        cmocka_unit_test(heap_size__heap__fiftySize),
        cmocka_unit_test(heap_size__heap__twentySize)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
