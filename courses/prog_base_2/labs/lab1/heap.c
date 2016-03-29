#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "memory.h"

#define MAX_SIZE 100

static memory_t * memory_new(heap_t * self, int size);
static void memory_free(memory_t * memory);


struct memory_s {
    char * mas;
    int count;
    int size;
    heap_t * heap;
};

struct heap_s {
    char mas[MAX_SIZE];
    int count;
    int size;
};


heap_t * heap_new(void) {
    int i;

    heap_t * p = malloc(sizeof(struct heap_s));
    p->count = 0;
    p->size = 0;

    for(i = 0; i < MAX_SIZE; i++) {
        p->mas[i] = '_';
    }
    return p;
}

void heap_free(heap_t * self) {
    free(self);
}

memory_t * heap_memory_allocate(heap_t * self, int size) {
    memory_t * point;
    if (self->size + size <= MAX_SIZE) {
        point = memory_new(self, size);
        self->size += size;
    }
    point->heap = self;
    return point;
}

void heap_memory_clear(heap_t * self, memory_t * memory) {
    int i;
    char * point = memory->mas;

    for(i = 0; i < memory->size; i++) {
        *point = '_';
        point++;
    }
    self->count -= memory->count;
    self->size -= memory->size;

    memory_free(memory);
}

int heap_count(heap_t * self) {
    return self->count;
}

int heap_size(heap_t * self) {
    return self->size;
}

char * heapMas (heap_t * self) {
    int i;
    char * heap = malloc(MAX_SIZE+1);

    for (i = 0; i < MAX_SIZE; i++) {
        heap[i] = self->mas[i];
    }
    heap[MAX_SIZE] = '\0';
    return heap;
}



static memory_t * memory_new(heap_t * self, int size) {
    memory_t * p = malloc(sizeof(struct memory_s));
    p->mas = self->mas + self->size;
    p->size = size;
    p->count = 0;
    return p;
}

static void memory_free(memory_t * memory) {
    free(memory);
}

int memory_count(memory_t * self) {
    return self->count;
}

int memory_size(memory_t * self) {
    return self->size;
}

void memory_set(memory_t * self, int offset, char * word, int length) {
    int i;
    char string[length];

    word += offset - 1;

    for(i = 0; i < length; i++) {
        string[i] = *word;
        word++;
    }

    char * point = self->mas + self->count;

    if (self->count + length <= self->size) {
        for(i = 0; i < length; i++) {
            *point = string[i];
            point++;
        }
        self->count += length;
        self->heap->count += length;
    }
}

char * memory_get(memory_t * self, int offset, int length) {
    char * point = self->mas;
    point += offset - 1;
    char * string;
    int size;
    int i;

    if(offset + length <= self->size)
        size = length;
    else
        size = self->size - offset + 1;

    string = malloc(sizeof(char) * size);

    for(i = 0; i < size; i++) {
        string[i] = *point;
        point++;
    }
    string[size] = '\0';

    return string;
}
