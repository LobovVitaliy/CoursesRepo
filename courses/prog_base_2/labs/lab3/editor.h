#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

#include "text.h"

typedef struct editor_s editor_t;

editor_t * editor_new(char * name);
void editor_free(editor_t * self);
//void editor_check(editor_t * self, text_t * text);

#endif // EDITOR_H_INCLUDED
