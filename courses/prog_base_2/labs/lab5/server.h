#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "http.h"

#include "cJSON.h"
#include "db_manager.h"

void server_homepage(socket_t * client);
void server_notFound(socket_t * client);

void server_masters(socket_t * client, http_request_t * req, db_t * db);
void server_mastersByID(socket_t * client, http_request_t * req, db_t * db);
void server_mastersHtml(socket_t * client, http_request_t * req, db_t * db);
void server_mastersHtmlByID(socket_t * client, http_request_t * req, db_t * db);
void server_mastersHtmlPOST(socket_t * client, http_request_t * req, db_t * db);

#endif

