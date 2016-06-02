#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

static int verification(char * name, char * surname, char * countK, char * countP)
{
    // check not Null
    if (name == NULL || surname == NULL || countK == NULL || countP == NULL)
    {
        return 0;
    }

    // check countK
    for (int i = 0; i < strlen(countK); i++)
    {
        if (!isdigit(countK[i]))
        {
            return 0;
        }
    }

    // check countP
    for (int i = 0; i < strlen(countP); i++)
    {
        if (!isdigit(countP[i]))
        {
            return 0;
        }
    }

    // check length
    if (strlen(name) == 0 || strlen(surname) == 0 ||
        strlen(countK) == 0 || strlen(countP) == 0 ||
        strlen(name) > 20 || strlen(surname) > 20
       )
    {
        return 0;
    }

    return 1;
}

static char * textToHTML(char * text)
{
    char * buffer = malloc(sizeof(char) * 10240);

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(text), text);

    return buffer;
}

static char * textToJSON(char * text)
{
    char * buffer = malloc(sizeof(char) * 10240);

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %zu\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(text), text);

    return buffer;
}



void server_homepage(socket_t * client)
{
    char buffer[1024] = "";
    char * pageText =
        "<h1>Hello, world of web!</h1>"
        "<a href=\"http://127.0.0.1:5000/ScrumMasters\">All Scrum Masters</a>";

    char * text = textToHTML(pageText);
    strcat(buffer, text);
    free(text);

    socket_write_string(client, buffer);
    socket_close(client);
}

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

void server_masters(socket_t * client, http_request_t * req, db_t * db)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        list_t * masters = list_new();

        char * countK = (char *)http_request_getArg(req, "countK");
        char * countP = (char *)http_request_getArg(req, "countP");

        if(countK != NULL && countP != NULL)
        {
            db_filtration(db, masters, atoi(countK), atoi(countP));
        }
        else
        {
            db_parse(db, masters);
        }

        cJSON * jPageText = cJSON_CreateArray();

        for(int i = 0; i < list_size(masters); i++)
        {
            master_t * sm = list_get(masters, i);

            cJSON * jText = cJSON_CreateObject();
            cJSON_AddItemToObject(jText, "Name", cJSON_CreateString(master_getName(sm)));
            cJSON_AddItemToObject(jText, "Surname", cJSON_CreateString(master_getSurname(sm)));
            cJSON_AddItemToObject(jText, "CountK", cJSON_CreateNumber(master_getCountK(sm)));
            cJSON_AddItemToObject(jText, "CountP", cJSON_CreateNumber(master_getCountP(sm)));
            cJSON_AddItemToArray(jPageText, jText);
        }

        char * pageText = cJSON_Print(jPageText);

        list_free(masters);

        char * textJSON = textToJSON(pageText);
        strcat(buffer, textJSON);
        free(textJSON);
    }
    else if (strcmp(req->method, "POST") == 0)
    {
        char * name = (char *)http_request_getArg(req, "name");
        char * surname = (char *)http_request_getArg(req, "surname");
        char * countK = (char *)http_request_getArg(req, "countK");
        char * countP = (char *)http_request_getArg(req, "countP");

        if(verification(name, surname, countK, countP) == 1)
        {
            db_insertData(db, name, surname, atoi(countK), atoi(countP));

            cJSON * jText = cJSON_CreateObject();
            cJSON_AddItemToObject(jText, "Name", cJSON_CreateString(name));
            cJSON_AddItemToObject(jText, "Surname", cJSON_CreateString(surname));
            cJSON_AddItemToObject(jText, "CountK", cJSON_CreateNumber(atoi(countK)));
            cJSON_AddItemToObject(jText, "CountP", cJSON_CreateNumber(atoi(countP)));
            char * pageText = cJSON_Print(jText);

            char * textJSON = textToJSON(pageText);
            strcat(buffer, textJSON);
            free(textJSON);
        }
        else
        {
            cJSON * jText = cJSON_CreateObject();
            cJSON_AddItemToObject(jText, "Error", cJSON_CreateString("Wrong input"));
            char * pageText = cJSON_Print(jText);

            char * textJSON = textToJSON(pageText);
            strcat(buffer, textJSON);
            free(textJSON);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_mastersByID(socket_t * client, http_request_t * req, db_t * db)
{
    char buffer[10240] = "";

    char * point = strstr(req->uri, "/api/ScrumMasters/");
    point += 18;
    int index = atoi(point);

    if(0 < index && index < db_count(db) + 1)
    {
        if (strcmp(req->method, "GET") == 0)
        {
            master_t * master = db_getDataById(db, index - 1);

            cJSON * jText = cJSON_CreateObject();
            cJSON_AddItemToObject(jText, "Name", cJSON_CreateString(master_getName(master)));
            cJSON_AddItemToObject(jText, "Surname", cJSON_CreateString(master_getSurname(master)));
            cJSON_AddItemToObject(jText, "CountK", cJSON_CreateNumber(master_getCountK(master)));
            cJSON_AddItemToObject(jText, "CountP", cJSON_CreateNumber(master_getCountP(master)));
            char * pageText = cJSON_Print(jText);

            free(master);

            char * textJSON = textToJSON(pageText);
            strcat(buffer, textJSON);
            free(textJSON);
        }
        else if (strcmp(req->method, "DELETE") == 0)
        {
            master_t * master = db_getDataById(db, index - 1);
            db_deleteData(db, master_getID(master));
            free(master);

            cJSON * jText = cJSON_CreateObject();
            cJSON_AddItemToObject(jText, "Success", cJSON_CreateString("Successfully deleted"));
            char * pageText = cJSON_Print(jText);

            char * textJSON = textToJSON(pageText);
            strcat(buffer, textJSON);
            free(textJSON);
        }
    }
    else
    {
        cJSON * jText = cJSON_CreateObject();
        cJSON_AddItemToObject(jText, "Error", cJSON_CreateString("ID Not Found"));
        char * pageText = cJSON_Print(jText);

        char * textJSON = textToJSON(pageText);
        strcat(buffer, textJSON);
        free(textJSON);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}



void server_mastersHtml(socket_t * client, http_request_t * req, db_t * db)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char pageText[10240] = "";

        for(int i = 0; i < db_count(db); i++)
        {
            master_t * master = db_getDataById(db, i);

            char text[100] = "";
            sprintf(text, "<a href=\"http://127.0.0.1:5000/ScrumMasters/%i\">%s %s<br></a>\n", i + 1, master_getSurname(master), master_getName(master));
            strcat(pageText, text);

            master_free(master);
        }

        char * text = "<a href=\"http://127.0.0.1:5000/new-ScrumMaster\"><br>New Scrum Master</a>";
        strcat(pageText, text);

        char * textHTML = textToHTML(pageText);
        strcat(buffer, textHTML);
        free(textHTML);
    }
    else if (strcmp(req->method, "POST") == 0)
    {
        char * name = (char *)http_request_getArg(req, "name");
        char * surname = (char *)http_request_getArg(req, "surname");
        char * countK = (char *)http_request_getArg(req, "countK");
        char * countP = (char *)http_request_getArg(req, "countP");

        if(verification(name, surname, countK, countP) == 1)
        {
            db_insertData(db, name, surname, atoi(countK), atoi(countP));

            char pageText[1024] = "";
            sprintf(pageText,
                    "<p>"
                    "Name: %s<br>"
                    "Surname: %s<br>"
                    "CountK: %i<br>"
                    "CountP: %i<br>"
                    "</p>",
                    name, surname,
                    atoi(countK),
                    atoi(countP));

            char * textHTML = textToHTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
        else
        {
            char * pageText = "<h3>Wrong input</h3>";
            char * textHTML = textToHTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_mastersHtmlByID(socket_t * client, http_request_t * req, db_t * db)
{
    char buffer[10240] = "";

    char * point = strstr(req->uri, "/ScrumMasters/");
    point += 14;
    int index = atoi(point);

    if(0 < index && index < db_count(db) + 1)
    {
        if (strcmp(req->method, "GET") == 0)
        {
            char pageText[10240] = "";

            master_t * master = db_getDataById(db, index - 1);

            char text[1024] = "";
            sprintf(text,
                    "<p>"
                    "Name: %s<br>"
                    "Surname: %s<br>"
                    "CountK: %i<br>"
                    "CountP: %i<br>"
                    "</p>",
                    master_getName(master),
                    master_getSurname(master),
                    master_getCountK(master),
                    master_getCountP(master));
            strcat(pageText, text);

            free(master);

            char * pageTextLink = "<a href=\"#\" onclick=\"doDelete()\"/>Delete Scrum Master<br><br></a>\n";
            strcat(pageText, pageTextLink);

            char pageTextScript[1024];
            sprintf(pageTextScript,
                        "<script>"
                        "function doDelete() {"
                        "var xhttp = new XMLHttpRequest();"
                        "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/ScrumMasters/%i\", true);"
                        "xhttp.send();"
                        "}"
                        "</script>", index);
            strcat(pageText, pageTextScript);

            char * textHTML = textToHTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
        else if (strcmp(req->method, "DELETE") == 0)
        {
            master_t * master = db_getDataById(db, index - 1);
            db_deleteData(db, master_getID(master));
            free(master);

            char * pageText = "<h4>Successfully deleted</h4>";
            sprintf(buffer,
                    "HTTP/1.1 200 OK\n"
                    "Content-Type: text/html\n"
                    "Content-Length: %zu\n"
                    "Access-Control-Allow-Origin: *\n"
                    "Access-Control-Allow-Methods: DELETE\n"
                    "\n%s",
                    strlen(pageText), pageText);
        }
    }
    else
    {
        char * pageText = "<h4>ID Not Found</h4>";
        char * textHTML = textToHTML(pageText);
        strcat(buffer, textHTML);
        free(textHTML);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_mastersHtmlPOST(socket_t * client, http_request_t * req, db_t * db)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char * pageText =
            "<form action=\"http://127.0.0.1:5000/ScrumMasters\" method=\"POST\">"
            "Name:<br>"
            "<input type=\"text\" name=\"name\" value='Ivan'><br>"
            "Surname:<br>"
            "<input type=\"text\" name=\"surname\" value='Ivanov'><br>"
            "CountK:<br>"
            "<input type=\"text\" name=\"countK\" value='3'><br>"
            "CountP:<br>"
            "<input type=\"text\" name=\"countP\" value='3'><br><br>"
            "<input type=\"submit\" value='Send POST request' />"
            "</form>";

            char * textHTML = textToHTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}
