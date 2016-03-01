#ifndef PLURAL_H_INCLUDED
#define PLURAL_H_INCLUDED

typedef struct plural_s plural_t;

plural_t * plural_new(void);

void plural_pf(plural_t * self);

void plural_free(plural_t * self);

void plural_add_element(int element, plural_t * self);
void plural_add_interval(int left, int right, plural_t * self);
void plural_delete_element(int element, plural_t * self);
void plural_delete_interval(int left, int right, plural_t * self);
void plural_difference(plural_t * first, plural_t * second);
void plural_association(plural_t * first, plural_t * second);
void plural_symmetric_difference(plural_t * first, plural_t * second);
int plural_power(plural_t * self);

#endif
