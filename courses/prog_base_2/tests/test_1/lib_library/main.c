#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "library.h"

typedef struct subscriber_s {
    void * listener;
    cb callback;
} subscriber_t;


struct user_s {
    char name[20];
};

user_t * user_new(char * name) {
    user_t * self = malloc(sizeof(struct user_s));
    strcpy(self->name, name);
    return self;
}

void user_free(user_t * self) {
    if(self != NULL) free(self);
}



struct book_s {
    list_t * users;
    int count;
    int status;
    int time;
};

book_t * book_new(char * name) {
    book_t * self = malloc(sizeof(struct book_s));
    self->users = list_new();
    self->count = 0;
    self->status = 0;
    self->time = 0;
    return self;
}

void book_free(book_t * self) {
    if(self != NULL) {
        list_free(self->users);
        free(self);
    }
}

int book_countUsers(book_t * self) {
    if(self != NULL)
        return self->count;
    else
        return -1;
}

void book_addUser(book_t * self, user_t * user) {
    if(self != NULL && user != NULL) {
        list_add(self->users, user);
        self->count++;
        self->status = 1;
        self->time = 5 + rand() % 10;
    }
}

void book_finishRead(book_t * self) {
    if(self != NULL) {
        self->status = 0;
        self->time = 0;
    }
}

void book_setStatus(book_t * self, int status) {
    if(self != NULL) {
        self->status = status;
    }
}

int book_getStatus(book_t * self) {
    if(self != NULL)
        return self->status;
    else
        return -1;
}

void book_setTime(book_t * self, int time) {
    if(self != NULL) {
        self->time = time;
    }
}

int book_getTime(book_t * self) {
    if(self != NULL)
        return self->time;
    else
        return -1;
}


struct library_s {
    list_t * subscribers; // подписчики
    list_t * books;
    int count;
};

library_t * library_new() {
    library_t * self = malloc(sizeof(struct library_s));
    self->subscribers = list_new(); // подписчики
    self->books = list_new();
    self->count = 0;
    return self;
}

void library_free(library_t * self) {
    if(self != NULL) {
        list_free(self->subscribers); // подписчики
        list_free(self->books);
        free(self);
    }
}

int library_countBooks(library_t * self) {
    if(self != NULL)
        return self->count;
    else
        return -1;
}

void library_addBook(library_t * self, book_t * book) {
    if(self != NULL && book != NULL) {
        list_add(self->books, book);
        self->count++;
    }
}

book_t * library_removeBook(library_t * self, int  index) {
    book_t * del = NULL;
    if(self != NULL && index > -1 && index < 100) {
        del = list_remove(self->books, index);
        self->count--;
    }
    return del;
}

list_t * library_getBooks(library_t * self) {
    if(self != NULL)
        return self->books;
    else
        return NULL;
}

list_t * library_getFreeBooks(library_t * self) {
    list_t * freeBooks = list_new();

    if(self != NULL) {
        for(int i = 0; i < self->count; i++) {
            if(book_getStatus((book_t*)list_get(self->books, i)) == 0) {
                list_add(freeBooks, (book_t*)list_get(self->books, i));
            }
        }
    }
    else {
        list_free(freeBooks);
        return NULL;
    }

    return freeBooks;
}

list_t * library_getNotFreeBooks(library_t * self) {
    list_t * NotFreeBooks = list_new();

    if(self != NULL) {
        for(int i = 0; i < self->count; i++) {
            if(book_getStatus((book_t*)list_get(self->books, i)) == 1) {
                list_add(NotFreeBooks, (book_t*)list_get(self->books, i));
            }
        }
    }
    else {
        list_free(NotFreeBooks);
        return NULL;
    }

    return NotFreeBooks;
}

list_t * library_getBooksTime(library_t * self, int timeN) {
    list_t * books = list_new();

    if(self != NULL && timeN > 0) {
        for(int i = 0; i < self->count; i++) {
            if((book_getTime((book_t*)list_get(self->books, i)) > timeN) && book_getStatus((book_t*)list_get(self->books, i)) != 0) {
                list_add(books, (book_t*)list_get(self->books, i));
            }
        }
    }
    else {
        list_free(books);
        return NULL;
    }

    return books;
}


void library_subscribe(library_t * self, void * listener, cb callback) {
    subscriber_t * sub = malloc(sizeof(struct subscriber_s));
    sub->listener = listener;
    sub->callback = callback;
    list_add(self->subscribers, sub);
}

void library_unsubscribe(library_t * self, void * listener, cb callback) {
    for (int i = 0; i < list_size(self->subscribers); i++) {
        subscriber_t * subs = (subscriber_t *)list_get(self->subscribers, i);
        if ((subs->listener == listener) && (subs->callback == callback)) {
            list_remove(self->subscribers, i);
            break;
        }
    }
}

void library_doCallbak(library_t * self) {
    for (int i = 0; i < list_size(self->subscribers); i++) {
        subscriber_t * sub = (subscriber_t *)list_get(self->subscribers, i);
        sub->callback(sub->listener);
    }
}
