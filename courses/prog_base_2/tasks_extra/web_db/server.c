#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

static char * textToHTML(char * text);

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

void server_homepage(socket_t * client)
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

void server_databases(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char pageText[10240] = "";

        for(int i = 0; i < (*countDB); i++)
        {
            char text[100] = "";
            sprintf(text, "<a href=\"http://127.0.0.1:5000/Database/%i\">%s<br><br></a>\n", i + 1, names[i]);
            strcat(pageText, text);
        }

        char * text = textToHTML(pageText);
        strcat(buffer, text);
        free(text);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_databasesByID(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char * point = strstr(req->uri, "/Database/");
        point += 10;
        int index = atoi(point);

        if(index > 0 && index < (*countDB) + 1)
        {
            char sqlQuery[1024] = "";
            sprintf(sqlQuery, "SELECT COUNT(*) FROM %s;", names[index - 1]);

            char sqlQueryID[1024] = "";
            sprintf(sqlQueryID, "SELECT * FROM %s;", names[index - 1]);

            char pageText[10240] = "";

            char first[1024] = "";
            sprintf(first,
                    "<table border=\"5\">"
                    "<caption>%s (Count: %i)</caption>"
                    "<tr>"
                    "<th>Id</th>"
                    "<th>Name</th>"
                    "<th>Surname</th>"
                    "<th></th>"
                    "<th></th>"
                    "</tr>",
                    names[index - 1],
                    db_count(db, sqlQuery)
                    );

            strcat(pageText, first);

            for(int i = 0; i < db_count(db, sqlQuery); i++)
            {
                entity_t * entity = db_getDataById(db, sqlQueryID, i);

                char second[1024] = "";
                sprintf(second,
                        "<tr>"
                        "<th>%i</th>"
                        "<th>%s</th>"
                        "<th>%s</th>"
                        "<th><a href=\"http://127.0.0.1:5000/Database/%i\" onclick=\"doDelete(%i)\"/>Delete</a></th>"
                        "<th><a href=\"http://127.0.0.1:5000/up-Database/%i/update/%i\" onclick=\"doUpdate(%i)\"/>Update</a></th>"
                        "</tr>",
                        entity_getID(entity),
                        entity_getName(entity),
                        entity_getSurname(entity),
                        index,
                        i + 1,
                        index,
                        i + 1,
                        i + 1);

                strcat(pageText, second);

                entity_free(entity);
            }

            strcat(pageText, "</table>");

            char third[1024] = "";
            sprintf(third,
                    "<a href=\"http://127.0.0.1:5000/new-Database/%i\"><br>New entry<br><br></a>"
                    "<a href=\"http://127.0.0.1:5000/Database\">All Databases</a>", index);
            strcat(pageText, third);

            char pageTextScriptDelete[1024];
            sprintf(pageTextScriptDelete,
                        "<script>"
                        "function doDelete(id) {"
                        "var xhttp = new XMLHttpRequest();"
                        "var url = \"http://127.0.0.1:5000/Database/%i/delete/\" + id;"
                        "xhttp.open(\"DELETE\", url, true);"
                        "xhttp.send();"
                        "}"
                        "</script>", index);
            strcat(pageText, pageTextScriptDelete);

            char pageTextScriptUpdate[1024];
            sprintf(pageTextScriptUpdate,
                        "<script>"
                        "function doUpdate(id) {"
                        "var xhttp = new XMLHttpRequest();"
                        "var url = \"http://127.0.0.1:5000/up-Database/%i/update/\" + id;"
                        "xhttp.open(\"PUT\", url, true);"
                        "xhttp.send();"
                        "}"
                        "</script>", index);
            strcat(pageText, pageTextScriptUpdate);

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
        else
        {
            char * pageText = "ERROR";

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
    }
    else if (strcmp(req->method, "POST") == 0)
    {
        char * point = strstr(req->uri, "/Database/");
        point += 10;
        int index = atoi(point);

        if(index > 0 && index < (*countDB) + 1)
        {
            char sqlQueryCount[1024] = "";
            sprintf(sqlQueryCount, "SELECT COUNT(*) FROM %s;", names[index - 1]);
            int count = db_count(db, sqlQueryCount);

            int indexNew = index;
            int countDigit = 0;
            while(0 != (int)indexNew)
            {
                indexNew = (int)indexNew / 10;
                countDigit++;
            }
            point += countDigit;
            if (strncmp(point, "/update/", 8) == 0)
            {
                point += 8;
                int indexUp = atoi(point);

                if(indexUp > 0 && indexUp < count + 1)
                {
                    char sqlQueryID[1024] = "";
                    sprintf(sqlQueryID, "SELECT * FROM %s;", names[index - 1]);
                    entity_t * entity = db_getDataById(db, sqlQueryID, indexUp - 1);

                    char sqlQueryUp[1024] = "";
                    sprintf(sqlQueryUp, "UPDATE %s SET Name = ?, Surname = ? WHERE ID = ?;", names[index - 1]);

                    char * name = (char *)http_request_getArg(req, "name");
                    char * surname = (char *)http_request_getArg(req, "surname");

                    if(strlen(name) != 0 && strlen(surname) != 0)
                        db_updateData(db, sqlQueryUp, entity_getID(entity), name, surname);

                    free(entity);

                    char pageText[10240] = "";
                    sprintf(pageText, "<a href=\"http://127.0.0.1:5000/Database/%i\">Return</a>", index);

                    sprintf(buffer,
                            "HTTP/1.1 200 OK\n"
                            "Content-Type: text/html\n"
                            "Content-Length: %zu\n"
                            "Access-Control-Allow-Origin: *\n"
                            "Access-Control-Allow-Methods: PUT\n"
                            "\n%s", strlen(pageText), pageText);
                }
                else
                {
                    char * pageText = "ERROR";

                    char * text = textToHTML(pageText);
                    strcat(buffer, text);
                    free(text);
                }
            }
            else
            {
                char sqlQueryNew[1024] = "";
                sprintf(sqlQueryNew, "INSERT INTO %s (Id, Name, Surname) VALUES (?, ?, ?);", names[index - 1]);

                char * id = (char *)http_request_getArg(req, "id");
                char * name = (char *)http_request_getArg(req, "name");
                char * surname = (char *)http_request_getArg(req, "surname");

                if(strlen(id) != 0 && strlen(name) != 0 && strlen(surname) != 0)
                    db_insertData(db, sqlQueryNew, atoi(id), name, surname);

                char pageText[10240] = "";
                sprintf(pageText, "<a href=\"http://127.0.0.1:5000/Database/%i\">Return</a>", index);

                char * text = textToHTML(pageText);
                strcat(buffer, text);
                free(text);
            }
        }
        else
        {
            char * pageText = "ERROR";

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
    }
    else if (strcmp(req->method, "DELETE") == 0)
    {
        char * point = strstr(req->uri, "/Database/");
        point += 10;
        int index = atoi(point);

        if(index > 0 && index < (*countDB) + 1)
        {
            int indexNew = index;
            int countDigit = 0;
            while(0 != (int)indexNew)
            {
                indexNew = (int)indexNew / 10;
                countDigit++;
            }
            point += countDigit;
            point += 8;
            int indexDel = atoi(point);

            char sqlQueryCount[1024] = "";
            sprintf(sqlQueryCount, "SELECT COUNT(*) FROM %s;", names[index - 1]);
            int count = db_count(db, sqlQueryCount);

            if(indexDel > 0 && indexDel < count + 1)
            {
                char sqlQueryID[1024] = "";
                sprintf(sqlQueryID, "SELECT * FROM %s;", names[index - 1]);
                entity_t * entity = db_getDataById(db, sqlQueryID, indexDel - 1);

                char sqlQueryDel[1024] = "";
                sprintf(sqlQueryDel, "DELETE FROM %s WHERE ID = ?;", names[index - 1]);
                db_deleteData(db, sqlQueryDel, entity_getID(entity));

                free(entity);

                sprintf(buffer,
                        "HTTP/1.1 200 OK\n"
                        "Access-Control-Allow-Origin: *\n"
                        "Access-Control-Allow-Methods: DELETE\n"
                        "\n");
            }
            else
            {
                char * pageText = "ERROR";

                char * text = textToHTML(pageText);
                strcat(buffer, text);
                free(text);
            }
        }
        else
        {
            char * pageText = "ERROR";

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_databaseNew(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char * point = strstr(req->uri, "/new-Database/");
        point += 14;
        int index = atoi(point);

        if(index > 0 && index < (*countDB) + 1)
        {
            char pageText[1024] = "";
            sprintf(pageText,
                    "<form action=\"http://127.0.0.1:5000/Database/%i\" method=\"POST\">"
                    "Id:<br>"
                    "<input type=\"text\" name=\"id\" value=0><br>"
                    "Name:<br>"
                    "<input type=\"text\" name=\"name\" value='Ivan'><br>"
                    "Surname:<br>"
                    "<input type=\"text\" name=\"surname\" value='Ivanov'><br><br>"
                    "<input type=\"submit\" value='Send POST request' />"
                    "</form>",
                    index);

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
        else
        {
            char * pageText = "ERROR";

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_databaseUpdate(socket_t * client, http_request_t * req, db_t * db, char ** names, int * countDB)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char * point = strstr(req->uri, "/up-Database/");
        point += 13;
        int index = atoi(point);

        if(index > 0 && index < (*countDB) + 1)
        {
            int indexNew = index;
            int countDigit = 0;
            while(0 != (int)indexNew)
            {
                indexNew = (int)indexNew / 10;
                countDigit++;
            }
            point += countDigit;
            point += 8;
            int indexUp = atoi(point);

            char pageText[1024] = "";
            sprintf(pageText,
                    "<form action=\"http://127.0.0.1:5000/Database/%i/update/%i\" method=\"POST\">"
                    "Name:<br>"
                    "<input type=\"text\" name=\"name\" value='Ivan'><br>"
                    "Surname:<br>"
                    "<input type=\"text\" name=\"surname\" value='Ivanov'><br><br>"
                    "<input type=\"submit\" value='Send PUT request' />"
                    "</form>",
                    index, indexUp);

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
        else
        {
            char * pageText = "ERROR";

            char * text = textToHTML(pageText);
            strcat(buffer, text);
            free(text);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}
