#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "editor.h"

struct editor_s {
    char * name;
    text_t * text;
};

editor_t * editor_new(char * name) {
    editor_t * self = malloc(sizeof(struct editor_s));
    self->name = name;
    return self;
}

void editor_free(editor_t * self) {
    free(self);
}

void editor_check(editor_t * self, text_t * text) {
    char str[512];
    strcpy(str, text_pop(text));
    printf("\nEditor %s detects an error: %s\n\n", self->name, str);
}
