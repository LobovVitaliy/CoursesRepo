#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

typedef struct memory_s memory_t;

int memory_count(heap_t * self, int index);
int memory_size(heap_t * self, int index);
void memory_set(heap_t * self, int index, int offset, char * word, int length);
char * memory_get(heap_t * self, int index, int offset, int length);

#endif
