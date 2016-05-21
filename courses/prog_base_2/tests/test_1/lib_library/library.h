#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "list.h"

typedef void (*cb)(void * listener);

typedef struct user_s user_t;
typedef struct book_s book_t;
typedef struct library_s library_t;

user_t * user_new(char * name);
void user_free(user_t * self);

book_t * book_new(char * name);
void book_free(book_t * self);
void book_addUser(book_t * self, user_t * user);
void book_finishRead(book_t * self);
void book_setStatus(book_t * self, int status);
int book_getStatus(book_t * self);
void book_setTime(book_t * self, int time);
int book_getTime(book_t * self);
int book_countUsers(book_t * self);
void book_addUser(book_t * self, user_t * user);

library_t * library_new();
void library_free(library_t * self);
int library_countBooks(library_t * self);
void library_addBook(library_t * self, book_t * book);
book_t * library_removeBook(library_t * self, int  index);
list_t * library_getBooks(library_t * self);
list_t * library_getFreeBooks(library_t * self);
list_t * library_getNotFreeBooks(library_t * self);
list_t * library_getBooksTime(library_t * self, int timeN);

void library_subscribe(library_t * self, void * listener, cb callback);
void library_unsubscribe(library_t * self, void * listener, cb callback);
void library_doCallbak(library_t * self);

#endif // LIBRARY_H_INCLUDED

