#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "list.h"

typedef struct text_s text_t;

typedef int (*cb) (text_t * text);

text_t * text_new();
void text_free(text_t * self);

void text_push(text_t * self, char * text);
char * text_pop(text_t * self);
int text_getSize(text_t * self);
int text_listGetSize(text_t * self);
char * text_getEl(text_t * self, int index);
void text_printf(text_t * self);

void text_subscribe(text_t * self, void * receiver, cb callback);
void text_check(text_t * self);

#endif // TEXT_H_INCLUDED

