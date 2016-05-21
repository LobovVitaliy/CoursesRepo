#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "ScrumMaster.h"
#include "http.h"

void server_homepage(socket_t * client);
void server_notFound(socket_t * client);
void server_masters(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size);
void server_mastersByID(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size);
void server_mastersHtml(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size);
void server_mastersHtmlPOST(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size);
void server_mastersHtmlByID(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size);

#endif

