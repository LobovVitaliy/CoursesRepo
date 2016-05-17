#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "text.h"

static void text_check(text_t * self);

struct text_s {
    char text[15][512];
    int size;
    list_t * event_notification;
    cb_fn double_cb;
    cb_fn overflow_cb;
    int statusD;
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

void test_setStatusD(text_t * self, int status) {
    self->statusD = status;
}

int test_getStatusD(text_t * self) {
    return self->statusD;
}

void test_subsDouble(text_t * self, cb_fn cb) {
    self->double_cb = cb;
    self->statusD = 0;
}

void test_subsOverflow(text_t * self, cb_fn cb) {
    self->overflow_cb = cb;
}

void text_push(text_t * self, char * text) {
    // @todo
    self->statusD = 0;
    for(int i = 0; i < self->size; i++) {
        if(strcmp(self->text[i], text) == 0) {
            self->double_cb(self, text);
            break;
        }
    }

    for(int i = 0; i < strlen(text); i++) {
        self->text[self->size][i] = text[i];
    }

    self->text[self->size][strlen(text)] = '\0';
    self->size++;
    text_check(self);

    if (self->size == 10) {
        self->overflow_cb(self, text);
    }
}

char * text_pop(text_t * self) {
    char str[512] = "";

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

static void text_check(text_t * self) {
    int count = list_getCount(self->event_notification);
    for (int i = 0; i < count; i++) {
        event_t * ev = list_getEl(self->event_notification, i);
        if (NULL != ev->callback) {
            cb fn = ev->callback;
            if(fn(text_getEl(self, self->size - 1)) == 1) {
                text_pop(self);
            }
        }
    }
}

void text_subscribe(text_t * self, cb callback) {
    event_t * sb = malloc(sizeof(struct event_s));
    //sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_notification, sb);
}
