#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef struct heap_s heap_t;

heap_t * heap_new(void);
void heap_free(heap_t * self);

char * heapMas (heap_t * self);
int heap_count(heap_t * self);
int heap_size(heap_t * self);

heap_t * heap_memory_allocate(heap_t * self, int index, int size);
void heap_memory_clear(heap_t * self, int index);

#endif

