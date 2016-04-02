//heap.c

// Done

/*struct memory_s {
    char * mas;
    int count;
};

struct heap_s {
    char mas[MAX_SIZE];
    int count;
    struct memory_s * memory;
};

heap_t * heap_new(void) {
    heap_t * p = malloc(sizeof(struct heap_s));
    p->count = 0;
    p->check = 1;
    return p;
}

void heap_free(heap_t * self) {
    memory_free(self);
    free(self);
}

heap_t * memory_allocate(heap_t * self, int size) {
    self->memory = memory_new(self, size);
    return self;
}

void memory_clear(heap_t * self) {
    memory_free(self);
}

static memory_t * memory_new(heap_t * self, int size) {
    memory_t * p = malloc(sizeof(struct memory_s));
    p->mas = self->mas;
    p->count = 0;
    return p;
}

static void memory_free(heap_t * self) {
    free(self->memory);
}

int memory_size(heap_t * self) {
    return self->memory->count;
}

void memory_set(heap_t * self, int offset, char * word, int length) {
    int i;

    char string[length + 1];
    word += offset - 1;

    for(i = 0; i < length; i++) {
        string[i] = *word;
        word++;
    }

    string[length] = '\0';

    char * point = self->memory->mas + self->memory->count;

    if (offset + length <= MAX_SIZE) {

        for(i = 0; i < length; i++) {
            *point = string[i];
            point++;
        }
        *(point + 1) = '\0';

        self->memory->count += length;
        self->count += length;
    }
}

char * memory_get(heap_t * self, int offset, int length) {
    int i;

    char * point = self->memory->mas;
    point += offset - 1;

    //char string[length + 1];
    char * string = malloc (sizeof(char) * (length + 1));

    for(i = 0; i < length; i++) {
        string[i] = *point;
        point++;
    }

    string[length] = '\0';

    return string;
}*/


//memory.c


/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

struct memory_s {
    char mas[60];
    int count;
};

memory_t * memory_new(void) {
    memory_t * p = malloc(sizeof(struct memory_s));
    p->count = 0;
    return p;
}

void memory_free(memory_t * self) {
    free(self);
}

int memory_size(memory_t * self) {
    return self->count;
}



heap_t * h = heap_new();
memory_t * m = heap_alloc(h, 30);
char * str = "Google";
mem_set(m, 5, str, 4));
char buf[3];
mem_get(m, 2, buf, 3);


void memory_set(memory_t * self, int offset, char * word, int length) {
void memory_set(char * word, memory_t * self) {
    int i,j;
    int count = self->count;

    if (strlen(word) <= 60 - count) {
        for (i = count, j = 0; i < count + strlen(word); i++, j++) {
            self->mas[i] = word[j];
            self->count++;
        }
    }

    printf("mas = %s\n", self->mas);
}

char * memory_get(char * word, memory_t * self, int beg, int end) {
    int i,j;

    for (i = beg, j = 0; i < end; i++, j++) {
        word[j] = self->mas[i];
    }

    return &word;
}*/
