#include <stdlib.h>
#include <stdio.h>

#include "list.h"

struct list_s {
    void * mas[100];
    int size;
};

list_t * list_new() {
    list_t * self = malloc(sizeof(struct list_s));
    self->size = 0;
    return self;
}

void list_free(list_t * self) {
    free(self);
}

void list_add(list_t * self, void * info) {
    if(self->size < 100) self->mas[self->size] = info;
    self->size++;
}

void * list_remove(list_t * self, int index) {
    void * del = self->mas[index];
    for(int i = index; i < self->size - 1; i++) {
        self->mas[i] = self->mas[i + 1];
    }
    self->size--;
    return del;
}

void * list_get(list_t * self, int index) {
    return self->mas[index];
}

int list_size(list_t * self) {
    return self->size;
}

int list_isEmpty(list_t * self) {
    if(self->size > 0)
        return 1;
    else
        return 0;
}

