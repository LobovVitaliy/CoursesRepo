#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  // ptrdiff_t
#include <string.h>
#include <ctype.h>

#include "socket.h"
#include "http.h"

#include "ScrumMaster.h"
#include "cJSON.h"

void parse(master ** ScrumMasters)
{
    FILE * file = fopen("ScrumMaster.json", "r");
    char text[10000];
    char line[100];

    while(fgets(line, 100, file) != NULL)
    {
        strcat(text, line);
    }
    fclose(file);

    cJSON * jList = cJSON_Parse(text);
    if (!jList)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(jList); i++)
    {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        char * name = cJSON_GetObjectItem(jItem, "name")->valuestring;
        char * surname = cJSON_GetObjectItem(jItem, "surname")->valuestring;
        char * date = cJSON_GetObjectItem(jItem, "date")->valuestring;
        int count = cJSON_GetObjectItem(jItem, "count")->valueint;
        double score = cJSON_GetObjectItem(jItem, "score")->valuedouble;

        master_set(ScrumMasters[i], name, surname, date, count, score);
    }
    cJSON_Delete(jList);
}


int verification(char * name, char * surname, char * date, char * count, char * score)
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
        }
        strcat(text, "]");

        sprintf(buffer,
                "HTTP/1.1 200 OK\n"
                "Content-Type: application/json\n"
                "Content-Length: %zu\n"
                "Connection: keep-alive\n"
                "\n%s", strlen(text), text);
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
            char * jSm = master_toJSON(ScrumMasters[*size], 0);
            (*size)++;

            sprintf(buffer,
                    "HTTP/1.1 200 OK\n"
                    "Content-Type: application/json\n"
                    "Content-Length: %zu\n"
                    "Connection: keep-alive\n"
                    "\n%s", strlen(jSm), jSm);
        }
        else
        {
            char * pageText = "{\n    \"Error\": \"Wrong input\"\n}";

            sprintf(buffer,
                    "HTTP/1.1 200 OK\n"
                    "Content-Type: application/json\n"
                    "Content-Length: %zu\n"
                    "Connection: keep-alive\n"
                    "\n%s", strlen(pageText), pageText);
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

        const char * pageTextBeg =
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "<meta charset=\"UTF-8\">\n"
            "<title>Sample</title>\n"
            "</head>\n"
            "<body>\n"
            "<h3>All Scrum Masters:</h3>\n";
        strcat(text, pageTextBeg);


        for(int i = 0; i < (*size); i++)
        {
            char pageText[100] = "";
            sprintf(pageText, "<a href=\"http://127.0.0.1:5000/ScrumMasters/%i\">%s %s<br></a>\n", i, getSurname(ScrumMasters[i]), getName(ScrumMasters[i]));
            strcat(text, pageText);
        }

        const char * pageTextEnd =
            "<a href=\"http://127.0.0.1:5000/new-ScrumMaster\"><br>New<br></a>\n"
            "<a href=\"http://127.0.0.1:5000\"><br>Back</a>\n"
            "</body>\n"
            "</html>";
        strcat(text, pageTextEnd);

        sprintf(buffer,
                "HTTP/1.1 200 OK\n"
                "Content-Type: application/json\n"
                "Content-Length: %zu\n"
                "Connection: keep-alive\n"
                "\n%s", strlen(text), text);
    }
    else if (strcmp(req->method, "POST") == 0)
    {

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
            char * jSm = master_toJSON(ScrumMasters[index], 0);

            sprintf(buffer,
                    "HTTP/1.1 200 OK\n"
                    "Content-Type: application/json\n"
                    "Content-Length: %zu\n"
                    "Connection: keep-alive\n"
                    "\n%s", strlen(jSm), jSm);
        }
        else
        {
            char * pageText = "{\n    \"Error\": \"ID Not Found\"\n}";

            sprintf(buffer,
                    "HTTP/1.1 404 \n"
                    "Content-Type: text/html\n"
                    "Content-Length: %zu\n"
                    "\n%s", strlen(pageText), pageText);
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

            sprintf(buffer,
                    "HTTP/1.1 200 OK\n"
                    "Content-Type: application/json\n"
                    "Content-Length: %zu\n"
                    "Connection: keep-alive\n"
                    "\n%s", strlen("OK"), "OK");
        }
        else
        {
            char * pageText = "{\n    \"Error\": \"ID Not Found\"\n}";

            sprintf(buffer,
                    "HTTP/1.1 404 \n"
                    "Content-Type: text/html\n"
                    "Content-Length: %zu\n"
                    "\n%s", strlen(pageText), pageText);
        }
    }

    socket_write_string(client, buffer);
    socket_close(client);
}

void server_homepage(socket_t * client)
{
    char homeBuf[1024];
    const char * pageText =
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta charset=\"UTF-8\">"
        "<title>Sample</title>"
        "</head>"
        "<body>"
        "<h1>Hello, world of web!</h1>"
        "<a href=\"http://127.0.0.1:5000/ScrumMasters\">All Scrum Masters</a>"
        "</body>"
        "</html>";

    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(pageText), pageText);

    socket_write_string(client, homeBuf);
    socket_close(client);
}

void server_notFound(socket_t * client)
{
    const char * pageText = "404 Page Not Found!";
    char homeBuf[1024];

    sprintf(homeBuf,
            "HTTP/1.1 404 \n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(pageText), pageText);

    socket_write_string(client, homeBuf);
    socket_close(client);
}


int main()
{
    lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);

    char buffer[10000];
    socket_t * client = NULL;

    master * ScrumMasters[10];

    for (int i = 0; i < 10; i++)
    {
        ScrumMasters[i] = master_new();
    }

    parse(ScrumMasters);
    int size = 3;

    while(1)
    {
        client = socket_accept(server);
        socket_read(client, buffer, sizeof(buffer));
        printf(">> Got request:\n%s\n", buffer);

        http_request_t request = http_request_parse(buffer);

        if (strcmp(request.uri, "/") == 0)
        {
            server_homepage(client);
        }
        else if (strcmp(request.uri, "/api/ScrumMasters") == 0)
        {
            server_masters(client, &request, ScrumMasters, &size);
        }
        else if (strncmp(request.uri, "/api/ScrumMasters/", 18) == 0)
        {
            server_mastersByID(client, &request, ScrumMasters, &size);
        }

        else if (strcmp(request.uri, "/ScrumMasters") == 0)
        {
            server_mastersHtml(client, &request, ScrumMasters, &size);
        }
        else
        {
            server_notFound(client);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        master_free(ScrumMasters[i]);
    }

    socket_free(client);
    socket_free(server);
    lib_free();
    return 0;
}
