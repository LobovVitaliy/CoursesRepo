#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

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

static int file_exists(const char * filename)
{
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
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

        cJSON * jPageText = cJSON_CreateArray();

        for(int i = 0; i < list_size(master); i++)
        {
            master_t * sm = list_get(master, i);

            cJSON * jText = cJSON_CreateObject();
            cJSON_AddItemToObject(jText, "Name", cJSON_CreateString(master_getName(sm)));
            cJSON_AddItemToObject(jText, "Surname", cJSON_CreateString(master_getSurname(sm)));
            cJSON_AddItemToObject(jText, "Count", cJSON_CreateNumber(master_getCount(sm)));
            cJSON_AddItemToObject(jText, "Score", cJSON_CreateNumber(master_getScore(sm)));
            cJSON_AddItemToObject(jText, "Date", cJSON_CreateString(master_getDate(sm)));
            cJSON_AddItemToArray(jPageText, jText);
        }

        char * pageText = cJSON_Print(jPageText);

        char * text = textToJSON(pageText);
        strcat(buffer, text);
        free(text);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_fourth(socket_t * client, http_request_t * req)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char * point = strstr(req->uri, "/files/");
        point += 7;

        if(strlen(point) != 0)
        {
            char fileName[100] = "";
            strcat(fileName, point);
            strcat(fileName, ".txt");

            int statusFile = file_exists(fileName);
            if(statusFile == 1)
            {
                FILE * file = fopen(fileName, "r");


                char * text = textToJSON(fileName);
                strcat(buffer, text);
                free(text);
            }
            else
            {
                server_notFound(client);
            }
        }
        else
        {
            server_notFound(client);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}
