#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main()
{
    char * str = "VitaliyLobovWritesProgramme";

    heap_t * heap = heap_new();

        memory_t * mem1 = heap_memory_allocate(heap, 35);
        memory_t * mem2 = heap_memory_allocate(heap, 20);
        memory_t * mem3 = heap_memory_allocate(heap, 45);

        printf("Your string: %s\n\n", str);

        puts("First");
            memory_set(mem1, 8, str, 5);
            printf("\tString: %s\n", memory_get(mem1, 1, 35));
            printf("\tMemory count: %i\n", memory_count(mem1));
            printf("\tMemory size: %i\n", memory_size(mem1));

            puts("");

        puts("Third");
            memory_set(mem3, 1, str, 27);
            printf("\tString: %s\n", memory_get(mem3, 1, 45));
            printf("\tMemory count: %i\n", memory_count(mem3));
            printf("\tMemory size: %i\n", memory_size(mem3));

            puts("");

        puts("First");
            memory_set(mem1, 19, str, 9);
            printf("\tStr: %s\n", memory_get(mem1, 6, 35));
            printf("\tString: %s\n", memory_get(mem1, 1, 35));
            printf("\tMemory count: %i\n", memory_count(mem1));
            printf("\tMemory size: %i\n", memory_size(mem1));

            puts("");

        puts("Second");
            memory_set(mem2, 1, str, 7);
            printf("\tString: %s\n", memory_get(mem2, 1, 20));
            printf("\tMemory count: %i\n", memory_count(mem2));
            printf("\tMemory size: %i\n", memory_size(mem2));

            puts("");

            memory_set(mem2, 13, str, 6);
            printf("\tStr: %s\n", memory_get(mem2, 8, 20));
            printf("\tString: %s\n", memory_get(mem2, 1, 20));
            printf("\tMemory count: %i\n", memory_count(mem2));
            printf("\tMemory size: %i\n", memory_size(mem2));

            puts("");

        puts("Third");
            memory_set(mem3, 1, str, 7);
            printf("\tStr: %s\n", memory_get(mem3, 28, 45));
            printf("\tString: %s\n", memory_get(mem3, 1, 45));
            printf("\tMemory count: %i\n", memory_count(mem3));
            printf("\tMemory size: %i\n", memory_size(mem3));

            puts("");

        puts("First");
            memory_set(mem1, 1, str, 10);
            printf("\tStr: %s\n", memory_get(mem1, 15, 35));
            printf("\tString: %s\n", memory_get(mem1, 1, 35));
            printf("\tMemory count: %i\n", memory_count(mem1));
            printf("\tMemory size: %i\n", memory_size(mem1));

            puts("");

        puts("Third");
            memory_set(mem3, 1, str, 10);
            printf("\tStr: %s\n", memory_get(mem3, 35, 45));
            printf("\tString: %s\n", memory_get(mem3, 1, 45));
            printf("\tMemory count: %i\n", memory_count(mem3));
            printf("\tMemory size: %i\n", memory_size(mem3));

            printf("\tStr: %s\n", memory_get(mem3, 8, 17));

        printf("\nHeap: \n%s\n", heapMas(heap));

        puts("");

        printf("Heap count: %i\n", heap_count(heap));
        printf("Heap size: %i\n", heap_size(heap));

        heap_memory_clear(heap, mem1);
        heap_memory_clear(heap, mem2);
        heap_memory_clear(heap, mem3);

        printf("\nHeap: \n%s\n", heapMas(heap));

        puts("");

        printf("Heap count: %i\n", heap_count(heap));
        printf("Heap size: %i\n", heap_size(heap));

    heap_free(heap);
    return 0;
}
