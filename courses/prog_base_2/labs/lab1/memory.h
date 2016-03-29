#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

typedef struct memory_s memory_t;

int memory_count(memory_t * self);
int memory_size(memory_t * self);
void memory_set(memory_t * self, int offset, char * word, int length);
char * memory_get(memory_t * self, int offset, int length);

#endif
