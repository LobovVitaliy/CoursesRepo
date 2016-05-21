#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

static int verification(char * name, char * surname, char * date, char * count, char * score);
static char * textToBuffer_JSON(char * text);
static char * textToBuffer_HTML(char * text);

static int verification(char * name, char * surname, char * date, char * count, char * score)
{
    int checkNum = 0;

    // check date
    for (int i = 0; i < 4; i++)
    {
        if (!isdigit(date[i]))
        {
            checkNum++;
        }
    }
    if (date[4] != '-')
    {
        checkNum++;
    }
    for (int i = 5; i < 7; i++)
    {
        if (!isdigit(date[i]))
        {
            checkNum++;
        }
    }
    if (atoi(date + 5) > 12)
    {
        checkNum++;
    }
    if (date[7] != '-')
    {
        checkNum++;
    }
    for (int i = 8; i < 10; i++)
    {
        if (!isdigit(date[i]))
        {
            checkNum++;
        }
    }
    if (atoi(date + 8) > 31)
    {
        checkNum++;
    }

    // check count
    for (int i = 0; i < strlen(count); i++)
    {
        if (!isdigit(count[i]))
        {
            checkNum++;
        }
    }

    // check score
    int countDot = 0;
    for (int i = 0; i < strlen(score); i++)
    {
        if (!isdigit(score[i]) && score[i] != '.')
        {
            checkNum++;
        }
        if (score[i] == '.')
        {
            countDot++;
        }
    }
    if (countDot > 1)
    {
        checkNum++;
    }

    if (strlen(name) == 0 || strlen(surname) == 0 || strlen(date) != 10
            || strlen(count) == 0 || strlen(score) == 0 || strlen(score) > 5
            || strlen(name) > 20 || strlen(surname) > 20 || strlen(count) > 5
       )
    {
        checkNum++;
    }

    if (checkNum == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static char * textToBuffer_JSON(char * text)
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

static char * textToBuffer_HTML(char * text)
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
        "<h1>Hello, world of web!</h1>"
        "<a href=\"http://127.0.0.1:5000/ScrumMasters\">All Scrum Masters</a>";

    char * text = textToBuffer_HTML(pageText);
    strcat(buffer, text);
    free(text);

    socket_write_string(client, pageText);
    socket_close(client);
}

void server_notFound(socket_t * client)
{
    char buffer[1024] = "";
    char * pageText = "404 Page Not Found!";

    char * text = textToBuffer_HTML(pageText);
    strcat(buffer, text);
    free(text);

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_masters(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char text[10240] = "";
        char * jSm = NULL;

        strcat(text, "[");
        for(int i = 0; i < (*size); i++)
        {
            if(i == (*size) - 1)
                jSm = master_toJSON(ScrumMasters[i], 0);
            else
                jSm = master_toJSON(ScrumMasters[i], 1);

            strcat(text, jSm);
            if(i !=  (*size) - 1) strcat(text, ",");
        }
        strcat(text, "]");

        char * textHTML = textToBuffer_JSON(text);
        strcat(buffer, textHTML);
        free(textHTML);
    }
    else if (strcmp(req->method, "POST") == 0)
    {
        char * name = (char *)http_request_getArg(req, "name");
        char * surname = (char *)http_request_getArg(req, "surname");
        char * date = (char *)http_request_getArg(req, "date");
        char * count = (char *)http_request_getArg(req, "count");
        char * score = (char *)http_request_getArg(req, "score");

        if(verification(name, surname, date, count, score) == 1)
        {
            char pageText[1024] = "";
            master_set(ScrumMasters[*size], name, surname, date, atoi(count), atof(score));
            char * jSm = master_toJSON(ScrumMasters[*size], 0);
            strcat(pageText, jSm);
            (*size)++;

            char * textHTML = textToBuffer_JSON(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
        else
        {
            char * pageText = "{\n    \"Error\": \"Wrong input\"\n}";
            char * textHTML = textToBuffer_JSON(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_mastersByID(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char * point = strstr(req->uri, "/api/ScrumMasters/");
        point += 18;
        int index = atoi(point);

        if(0 <= index && index < (*size))
        {
            char pageText[1024] = "";
            char * jSm = master_toJSON(ScrumMasters[index], 0);
            strcat(pageText, jSm);
            char * textHTML = textToBuffer_JSON(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
        else
        {
            char * pageText = "{\n    \"Error\": \"ID Not Found\"\n}";
            char * textHTML = textToBuffer_JSON(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
    }
    else if (strcmp(req->method, "DELETE") == 0)
    {
        char * id = (char *)http_request_getArg(req, "id");
        int index = atoi(id);

        if(0 <= index && index < (*size))
        {
            for(int i = index; i < (*size) - 1; i++)
            {
                master_swap(ScrumMasters[i], ScrumMasters[i + 1]);
            }

            (*size)--;

            char * pageText = "{\n    \"Success\": \"Successfully deleted\"\n}";
            char * textHTML = textToBuffer_JSON(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
        else
        {
            char * pageText = "{\n    \"Error\": \"ID Not Found\"\n}";
            char * textHTML = textToBuffer_JSON(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_mastersHtml(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char text[10240] = "";

        for(int i = 0; i < (*size); i++)
        {
            char pageText[100] = "";
            sprintf(pageText, "<a href=\"http://127.0.0.1:5000/ScrumMasters/%i\">%s %s<br></a>\n", i, getSurname(ScrumMasters[i]), getName(ScrumMasters[i]));
            strcat(text, pageText);
        }

        char * pageText = "<a href=\"http://127.0.0.1:5000/new-ScrumMaster\"><br>New Scrum Master</a>";
        strcat(text, pageText);

        char * textHTML = textToBuffer_HTML(text);
        strcat(buffer, textHTML);
        free(textHTML);
    }
    else if (strcmp(req->method, "POST") == 0)
    {
        char * name = (char *)http_request_getArg(req, "name");
        char * surname = (char *)http_request_getArg(req, "surname");
        char * date = (char *)http_request_getArg(req, "date");
        char * count = (char *)http_request_getArg(req, "count");
        char * score = (char *)http_request_getArg(req, "score");

        if(verification(name, surname, date, count, score) == 1)
        {
            master_set(ScrumMasters[*size], name, surname, date, atoi(count), atof(score));
            char * pageText = "<h3>Success</h3>";
            (*size)++;

            char * textHTML = textToBuffer_HTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
        else
        {
            char * pageText = "<h3>Wrong input</h3>";
            char * textHTML = textToBuffer_HTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_mastersHtmlPOST(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size)
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
            "Date:<br>"
            "<input type=\"text\" name=\"date\" value='1950-05-04'><br>"
            "Count:<br>"
            "<input type=\"text\" name=\"count\" value='3'><br>"
            "Score:<br>"
            "<input type=\"text\" name=\"score\" value='4.5'><br><br>"
            "<input type=\"submit\" value='Send POST request' />"
            "</form>";

            char * textHTML = textToBuffer_HTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_mastersHtmlByID(socket_t * client, http_request_t * req, master ** ScrumMasters, int * size)
{
    char buffer[10240] = "";

    char * point = strstr(req->uri, "/ScrumMasters/");
    point += 14;
    int index = atoi(point);

    if(0 <= index && index < (*size))
    {
        if (strcmp(req->method, "GET") == 0)
        {
            char pageText[1024] = "";
            char * text = master_toHTML(ScrumMasters[index], index);
            strcat(pageText, text);
            free(text);

            char * textHTML = textToBuffer_HTML(pageText);
            strcat(buffer, textHTML);
            free(textHTML);
        }
        else if (strcmp(req->method, "DELETE") == 0)
        {
            for(int i = index; i < (*size) - 1; i++)
            {
                master_swap(ScrumMasters[i], ScrumMasters[i + 1]);
            }

            (*size)--;

            sprintf(buffer,
                    "HTTP/1.1 200 OK\n"
                    "Access-Control-Allow-Origin: *\n"
                    "Access-Control-Allow-Methods: DELETE\n"
                    "\n");
        }
    }
    else
    {
        char * pageText = "<h4>ID Not Found!</h4>";
        char * textHTML = textToBuffer_HTML(pageText);
        strcat(buffer, textHTML);
        free(textHTML);
    }

    socket_write_string(client, buffer);
    socket_close(client);
}
