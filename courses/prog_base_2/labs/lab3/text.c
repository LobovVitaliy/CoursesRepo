#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "text.h"

struct text_s {
    char text[15][512];
    int size;
    list_t * event_notification;
};

text_t * text_new() {
    text_t * self = malloc(sizeof(struct text_s));
    self->size = 0;
    self->event_notification = list_new();
    return self;
}

void text_free(text_t * self) {
    int count = list_getCount(self->event_notification);
    for (int i = 0; i < count; i++) {
        event_t * ev = list_pop_back(self->event_notification);
        free(ev);
    }
    list_free(self->event_notification);
    free(self);
}

void text_push(text_t * self, char * text) {
    for(int i = 0; i < strlen(text); i++)
        self->text[self->size][i] = text[i];
    self->text[self->size][strlen(text)] = '\0';
    self->size++;
}

char * text_pop(text_t * self) {
    static char str[512] = "";

    strcpy(str, self->text[self->size - 1]);
    self->text[self->size][0] = '\0';
    self->size--;

    return str;
}

int text_getSize(text_t * self) {
    return self->size;
}

int text_listGetSize(text_t * self) {
    return list_getCount(self->event_notification);
}

char * text_getEl(text_t * self, int index) {
    return self->text[index];
}


void text_printf(text_t * self) {
    puts("\nYour text:");
    for (int i = 0; i < self->size; i++)
        printf("%i) %s\n", i + 1, self->text[i]);
}


void text_check(text_t * self) {
    int count = list_getCount(self->event_notification);
    for (int i = 0; i < count; i++) {
        event_t * ev = list_getEl(self->event_notification, i);
        if (NULL != ev->callback) {
            cb fn = ev->callback;
            if(fn(self) == 1) {
                editor_check(ev->receiver, self);
            }
        }
    }
}

void text_subscribe(text_t * self, void * receiver, cb callback) {
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_notification, sb);
}
