#include "plural.h"

struct plural_s {
    int mas[10];
    int mas_overflow[20];
    int count;
};

plural_t * plural_new(void) {
    plural_t * p = malloc(sizeof(struct plural_s));
    p->count = 0;
    return p;
}


void plural_pf(plural_t * self) {
    int i;

    for(i = 0; i < self->count; i++) {
        printf("%i\t", self->mas[i]);
    }
}

void plural_pf_result(plural_t * self) {
    int i;

    for(i = 0; i < self->count; i++) {
        printf("%i\t", self->mas_overflow[i]);
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

plural_t * plural_difference(plural_t * first, plural_t * second, plural_t * result) {
    int check = 0;
    int i,j;

    for(i = 0; i < first->count; i++) {
        for(j = 0; j < second->count; j++) {
            if(first->mas[i] != second->mas[j]) {
                check++;
            }
        }
        if(check == second->count) {
            result->mas_overflow[result->count] = first->mas[i];
            result->count++;
        }
        check = 0;
    }

    return result;
}

plural_t * plural_association(plural_t * first, plural_t * second, plural_t * result) {
    int check = 0;
    int i,j;

    for(i = 0;  i < first->count; i++) {
        result->mas_overflow[result->count] = first->mas[i];
        result->count++;
    }

    for(i = 0; i < second->count; i++) {

        for(j = 0; j < first->count; j++) {
            if(second->mas[i] == first->mas[j]) {
                check = 1;
            }
        }

        if(check == 0) {
            result->mas_overflow[result->count] = second->mas[i];
            result->count++;
        }

        check = 0;
    }

    return result;
}

plural_t * plural_symmetric_difference(plural_t * first, plural_t * second, plural_t * result) {

    result = plural_difference(first, second, result);
    result = plural_difference(second, first, result);

    return result;
}

int plural_power(plural_t * self) {
    return self->count;
}

