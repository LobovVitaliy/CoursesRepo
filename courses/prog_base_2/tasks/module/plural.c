#include "plural.h"

struct plural_s {
    int mas[10];
    int count;
};

plural_t * plural_new(void) {
    plural_t * p = malloc(sizeof(plural_t));
    p->count = 0;
    return p;
}


void plural_pf(plural_t * self) {
    int i;

    for(i = 0; i < self->count; i++) {
        printf("%i\t", self->mas[i]);
    }
}

void plural_free(plural_t * self) {
    free(self);
}


void plural_add_element(int element, plural_t * self) {
    self->mas[self->count] = element;
    self->count++;
}

void plural_add_interval(int left, int right, plural_t * self) {
    int i;

    for(i = left; i <= right; i++) {
        self->mas[self->count] = i;
        self->count++;
    }
}

void plural_delete_element(int element, plural_t * self) {
    int i,j;

    for(i = self->count - 1; i >=0; i--) {
        if(self->mas[i] == element) {
            for(j = i; j < self->count - 1; j++) {
                self->mas[j] = self->mas[j+1];
            }
        }
    }
    self->count--;
}

void plural_delete_interval(int left, int right, plural_t * self) {
    int i,j,k;

    for(k = left; k <= right; k++) {
        for(i = self->count - 1; i >=0; i--) {
            if(self->mas[i] == k) {
                for(j = i; j < self->count - 1; j++) {
                    self->mas[j] = self->mas[j+1];
                }
            }
        }
        self->count--;
    }
}

void plural_difference(plural_t * first, plural_t * second) {
    plural_t * new_mas = plural_new();
    int check = 0;
    int i,j;

    for(i = 0; i < first->count; i++) {
        for(j = 0; j < second->count; j++) {
            if(first->mas[i] != second->mas[j]) {
                check++;
            }
        }
        if(check == second->count) {
            new_mas->mas[new_mas->count] = first->mas[i];
            new_mas->count++;
        }
        check = 0;
    }

    plural_pf(new_mas);
    plural_free(new_mas);
}

void plural_association(plural_t * first, plural_t * second) {
    plural_t * new_mas = plural_new();
    int check = 0;
    int error = 1;
    int i,j;

    for(i = 0;  i < first->count; i++) {
        new_mas->mas[new_mas->count] = first->mas[i];
        new_mas->count++;
    }

    for(i = 0; i < second->count; i++) {

        if(new_mas->count > 9) {
            error = 0;
            break;
        }

        for(j = 0; j < first->count; j++) {
            if(second->mas[i] == first->mas[j]) {
                check = 1;
            }
        }

        if(check == 0) {
            new_mas->mas[new_mas->count] = second->mas[i];
            new_mas->count++;
        }

        check = 0;
    }

    plural_pf(new_mas);
    plural_free(new_mas);

    if(error == 0) {
        printf("Error: Overflow");
    }
}

void plural_symmetric_difference(plural_t * first, plural_t * second) {
    plural_t * new_mas = plural_new();

    plural_difference(first, second);
    plural_difference(second, first);

    plural_pf(new_mas);
    plural_free(new_mas);
}

int plural_power(plural_t * self) {
    return self->count;
}

