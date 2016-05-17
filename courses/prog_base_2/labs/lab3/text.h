#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "list.h"

typedef struct text_s text_t;

typedef void (*cb_fn)(text_t * self, char * newSent);
typedef int (*cb) (char * str);

text_t * text_new();
void text_free(text_t * self);

void text_push(text_t * self, char * text);
char * text_pop(text_t * self);
int text_getSize(text_t * self);
int text_listGetSize(text_t * self);
char * text_getEl(text_t * self, int index);
void text_printf(text_t * self);

void test_setStatusD(text_t * self, int status);
int test_getStatusD(text_t * self);

void text_subscribe(text_t * self, cb callback);
void test_subsDouble(text_t * self, cb_fn cb);
void test_subsOverflow(text_t * self, cb_fn cb);

#endif // TEXT_H_INCLUDED

