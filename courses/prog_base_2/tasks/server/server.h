#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "ScrumMaster.h"

typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct {
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
} http_request_t;

void server_reply(socket_t * clientSocket, http_request_t req, master ** scrumMaster);

void error(socket_t * clientSocket, char * str);
int findIndex (http_request_t req);

void getItems(socket_t * clientSocket, master ** scrumMaster);
void getItemsID(socket_t * clientSocket, master * scrumMaster);
void deleteItemsID(socket_t * clientSocket, master * scrumMaster);
void postItemsID(socket_t * clientSocket, http_request_t req, master * scrumMaster);

http_request_t http_request_parse(const char * const request);
const char * http_request_getArg(http_request_t * self, const char * key);
const char * keyvalue_toString(keyvalue_t * self);

#endif
