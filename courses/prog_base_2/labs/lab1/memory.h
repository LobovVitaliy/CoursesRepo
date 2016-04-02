#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

typedef struct memory_s memory_t;

enum memory_status_t {MEMORY_NO_OK, MEMORY_OK};

int memory_count(memory_t * self);
int memory_size(memory_t * self);
void memory_set(memory_t * self, int offset, char * word, int length);
char * memory_get(memory_t * self, int offset, int length);

enum memory_status_t memory_status(memory_t * self);

#endif
