#include "queue.h"

struct queue_s {
    int array[100];
    int count;
};

queue_t * queue_new(void) {
    queue_t * q = malloc(sizeof(struct queue_s));
    q->count = 0;
    return q;
}

void queue_free(queue_t * self) {
    free(self);
}

int queue_getElement(queue_t * self, int index) {
    if (index < self->count)
        return self->array[index];
}

void queue_add(queue_t * self, int val) {
    self->array[self->count] = val;
    self->count++;
}

int queue_delete(queue_t * self) {
    int val = self->array[0];
    for (int i = 0; i < self->count - 1; i++) {
        self->array[i] = self->array[i + 1];
    }
    self->count--;
    return val;
}

int queue_getCount(queue_t * self) {
    return self->count;
}

void queue_print(queue_t * self) {
    for(int i = 0; i < self->count; i++) {
        printf("%3i ", self->array[i]);
    }
}
