#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

static char * textToJSON(char * text);
static char * textToJSON(char * text)
{
    char * buffer = malloc(sizeof(char) * 10240);

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/json\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(text), text);

    return buffer;
}

/*void server_homepage(socket_t * client)
{
    char buffer[1024] = "";
    char * pageText =
        "<h1>Database!</h1>"
        "<a href=\"http://127.0.0.1:5000/Database\">All Databases</a>";

    char * text = textToHTML(pageText);
    strcat(buffer, text);
    free(text);

    socket_write_string(client, buffer);
    socket_close(client);
}*/

void server_notFound(socket_t * client)
{
    char buffer[1024] = "";
    char * pageText = "404 Page Not Found!";

    sprintf(buffer,
            "HTTP/1.1 404 Not Found\n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(pageText), pageText);

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_first(socket_t * client, http_request_t * req)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        cJSON * jText = cJSON_CreateObject();
        cJSON_AddItemToObject(jText, "student", cJSON_CreateString("Vitaliy Lobov"));
        cJSON_AddItemToObject(jText, "group", cJSON_CreateString("KP-51"));
        cJSON_AddItemToObject(jText, "variant", cJSON_CreateNumber(20));
        char * pageText = cJSON_Print(jText);

        char * text = textToJSON(pageText);
        strcat(buffer, text);
        free(text);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_third(socket_t * client, http_request_t * req, db_t * db, list_t * master)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        db_parse(db, master);
        char * x = master_getName(list_get(master, 0));
        //puts(x);
        char * text = textToJSON(x);
        strcat(buffer, text);
        free(text);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}
