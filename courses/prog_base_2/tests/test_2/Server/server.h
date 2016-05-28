#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "http.h"
#include "cJSON.h"
#include "db_manager.h"

void server_notFound(socket_t * client);
void server_first(socket_t * client, http_request_t * req);
void server_second(socket_t * client, http_request_t * req);
void server_third(socket_t * client, http_request_t * req, db_t * db, list_t * master);
void server_fourth(socket_t * client, http_request_t * req);

#endif
