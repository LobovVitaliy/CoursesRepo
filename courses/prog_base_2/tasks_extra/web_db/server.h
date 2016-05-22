#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "http.h"
#include "db_manager.h"

void server_homepage(socket_t * client);
void server_notFound(socket_t * client);
void server_databases(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB);
void server_databasesByID(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB);
void server_databaseNew(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB);
void server_databaseUpdate(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB);

#endif

