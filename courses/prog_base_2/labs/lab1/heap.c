#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "memory.h"

#define MAX_SIZE 100

static memory_t * memory_new(heap_t * self, int size);
static void memory_free(heap_t * self, int index);


struct memory_s {
    char * mas;
    int count;
    int size;
};

struct heap_s {
    char mas[MAX_SIZE];
    int count;
    struct memory_s * memory[3];
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

heap_t * heap_memory_allocate(heap_t * self, int index, int size) {
    if (self->size + size <= MAX_SIZE) {
        self->memory[index] = memory_new(self, size);
        self->size += size;
        return self;
    }
    return NULL;
}

void heap_memory_clear(heap_t * self, int index) {
    int i;
    char * point = self->memory[index]->mas;

    for(i = 0; i < self->memory[index]->size; i++) {
        *point = '_';
        point++;
    }
    self->count -= self->memory[index]->count;
    self->size -= self->memory[index]->size;

    memory_free(self, index);
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

static void memory_free(heap_t * self, int index) {
    free(self->memory[index]);
}

int memory_count(heap_t * self, int index) {
    return self->memory[index]->count;
}

int memory_size(heap_t * self, int index) {
    return self->memory[index]->size;
}

void memory_set(heap_t * self, int index, int offset, char * word, int length) {
    int i;
    char string[length];

    word += offset - 1;

    for(i = 0; i < length; i++) {
        string[i] = *word;
        word++;
    }

    char * point = self->memory[index]->mas + self->memory[index]->count;

    if (self->memory[index]->count + length <= self->memory[index]->size) {
        for(i = 0; i < length; i++) {
            *point = string[i];
            point++;
        }
        self->memory[index]->count += length;
        self->count += length;
    }
}

char * memory_get(heap_t * self, int index, int offset, int length) {
    char * point = self->memory[index]->mas;
    point += offset - 1;
    char * string;
    int size;
    int i;

    if(offset + length <= self->memory[index]->size)
        size = length;
    else
        size = self->memory[index]->size - offset + 1;

    string = malloc(sizeof(char) * size);

    for(i = 0; i < size; i++) {
        string[i] = *point;
        point++;
    }
    string[size] = '\0';

    return string;
}
