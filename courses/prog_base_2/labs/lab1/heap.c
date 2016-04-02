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
    enum memory_status_t status;
    heap_t * heap;
};

struct heap_s {
    char mas[MAX_SIZE];
    int count;
    int size;
    enum heap_status_t status;
};


heap_t * heap_new(void) {
    int i;

    heap_t * p = malloc(sizeof(struct heap_s));
    p->count = 0;
    p->size = 0;

    for(i = 0; i < MAX_SIZE; i++) {
        p->mas[i] = '_';
    }
    p->status = HEAP_OK;
    return p;
}

void heap_free(heap_t * self) {
    if(self != NULL) {
        free(self);
    }
}





memory_t * heap_memory_allocate(heap_t * self, int size) {
    memory_t * point = NULL;
    if(self != NULL && size > 0) {
        if (self->size + size <= MAX_SIZE) {
            point = memory_new(self, size);
            point->heap = self;
            self->size += size;
            self->status = HEAP_OK;
        }
        else
            self->status = HEAP_NO_OK;
    }
    return point;
}

void heap_memory_clear(heap_t * self, memory_t * memory) {
    char * point;
    int i;

    if(self != NULL && memory != NULL) {
        point = memory->mas;

        for(i = 0; i < memory->size; i++) {
            *point = '_';
            point++;
        }
        self->count -= memory->count;
        self->size -= memory->size;

        self->status = HEAP_OK;

        memory_free(memory);
    }
}

int heap_count(heap_t * self) {
    if(self != NULL) {
        self->status = HEAP_OK;
        return self->count;
    }
    return -1;
}

int heap_size(heap_t * self) {
    if(self != NULL) {
        self->status = HEAP_OK;
        return self->size;
    }
    return -1;
}

char * heapMas (heap_t * self) {
    int i;
    char * heap = NULL;

    if(self != NULL) {
        heap = malloc(MAX_SIZE + 1);

        self->status = 1;

        for (i = 0; i < MAX_SIZE; i++) {
            heap[i] = self->mas[i];
        }
        heap[MAX_SIZE] = '\0';
    }
    return heap;
}

enum heap_status_t heap_status(heap_t * self) {
    if(self != NULL) {
        return self->status;
    }
    return HEAP_NO_OK;
}


static memory_t * memory_new(heap_t * self, int size) {
    memory_t * p = NULL;

    if(self != NULL && size > 0) {
        p = malloc(sizeof(struct memory_s));
        p->mas = self->mas + self->size;
        p->size = size;
        p->count = 0;
        p->status = MEMORY_OK;
    }
    return p;
}

static void memory_free(memory_t * self) {
    if(self != NULL) {
        free(self);
    }
}

int memory_count(memory_t * self) {
    if(self != NULL) {
        self->status = MEMORY_OK;
        return self->count;
    }
    return -1;
}

int memory_size(memory_t * self) {
    if(self != NULL) {
        self->status = MEMORY_OK;
        return self->size;
    }
    return -1;
}

void memory_set(memory_t * self, int offset, char * word, int length) {
    int i;

    if(self != NULL) {
        if (word != NULL && offset > 0 && length > 0) {
            if(length > strlen(word))
                length = strlen(word) - offset + 1;

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
                self->status = MEMORY_OK;
            }
            else
                self->status = MEMORY_NO_OK;
        }
        else
            self->status = MEMORY_NO_OK;
    }
}

char * memory_get(memory_t * self, int offset, int length) {
    char * string = NULL;

    if(self != NULL) {
        if (offset > 0 && length > 0) {
            char * point = self->mas;
            point += offset - 1;
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

            self->status = MEMORY_OK;
        }
        else
            self->status = MEMORY_NO_OK;
    }
    return string;
}

enum memory_status_t memory_status(memory_t * self) {
    if(self != NULL) {
        return self->status;
    }
    return MEMORY_NO_OK;
}
