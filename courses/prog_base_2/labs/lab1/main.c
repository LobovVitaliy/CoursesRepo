#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

enum memory {first, second, third};

int main()
{
    char * str = "VitaliyLobovWritesProgramme";

    heap_t * heap = heap_new();

        heap = heap_memory_allocate(heap, first, 35);
        heap = heap_memory_allocate(heap, second, 20);
        heap = heap_memory_allocate(heap, third, 45);

        printf("Your string: %s\n\n", str);

        puts("First");
            memory_set(heap, first, 8, str, 5);
            printf("\tString: %s\n", memory_get(heap, first, 1, 35));
            printf("\tMemory count: %i\n", memory_count(heap, first));
            printf("\tMemory size: %i\n", memory_size(heap, first));

            puts("");

        puts("Third");
            memory_set(heap, third, 1, str, 27);
            printf("\tString: %s\n", memory_get(heap, third, 1, 45));
            printf("\tMemory count: %i\n", memory_count(heap, third));
            printf("\tMemory size: %i\n", memory_size(heap, third));

            puts("");

        puts("First");
            memory_set(heap, first, 19, str, 9);
            printf("\tStr: %s\n", memory_get(heap, first, 6, 35));
            printf("\tString: %s\n", memory_get(heap, first, 1, 35));
            printf("\tMemory count: %i\n", memory_count(heap, first));
            printf("\tMemory size: %i\n", memory_size(heap, first));

            puts("");

        puts("Second");
            memory_set(heap, second, 1, str, 7);
            printf("\tString: %s\n", memory_get(heap, second, 1, 20));
            printf("\tMemory count: %i\n", memory_count(heap, second));
            printf("\tMemory size: %i\n", memory_size(heap, second));

            puts("");

            memory_set(heap, second, 13, str, 6);
            printf("\tStr: %s\n", memory_get(heap, second, 8, 20));
            printf("\tString: %s\n", memory_get(heap, second, 1, 20));
            printf("\tMemory count: %i\n", memory_count(heap, second));
            printf("\tMemory size: %i\n", memory_size(heap, second));

            puts("");

        puts("Third");
            memory_set(heap, third, 1, str, 7);
            printf("\tStr: %s\n", memory_get(heap, third, 28, 45));
            printf("\tString: %s\n", memory_get(heap, third, 1, 45));
            printf("\tMemory count: %i\n", memory_count(heap, third));
            printf("\tMemory size: %i\n", memory_size(heap, third));

            puts("");

        puts("First");
            memory_set(heap, first, 1, str, 10);
            printf("\tStr: %s\n", memory_get(heap, first, 15, 35));
            printf("\tString: %s\n", memory_get(heap, first, 1, 35));
            printf("\tMemory count: %i\n", memory_count(heap, first));
            printf("\tMemory size: %i\n", memory_size(heap, first));

            puts("");

        puts("Third");
            memory_set(heap, third, 1, str, 10);
            printf("\tStr: %s\n", memory_get(heap, third, 35, 45));
            printf("\tString: %s\n", memory_get(heap, third, 1, 45));
            printf("\tMemory count: %i\n", memory_count(heap, third));
            printf("\tMemory size: %i\n", memory_size(heap, third));

            printf("\tStr: %s\n", memory_get(heap, third, 8, 17));

        printf("\nHeap: \n%s\n", heapMas(heap));

        puts("");

        printf("Heap count: %i\n", heap_count(heap));
        printf("Heap size: %i\n", heap_size(heap));

        heap_memory_clear(heap, first);
        heap_memory_clear(heap, second);
        heap_memory_clear(heap, third);

        printf("\nHeap: \n%s\n", heapMas(heap));

        puts("");

        printf("Heap count: %i\n", heap_count(heap));
        printf("Heap size: %i\n", heap_size(heap));

    heap_free(heap);
    return 0;
}
