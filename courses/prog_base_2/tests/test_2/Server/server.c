#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

#include "server.h"

typedef struct entity_s {
    char movie[256];
    int year;
    char time[25];
} entity_t;

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

void server_second(socket_t * client, http_request_t * req)
{
    char buffer[10240] = "";

    if (strcmp(req->method, "GET") == 0)
    {
        char textServer[10240] = "";
        char pageText[10240] = "";

        lib_init();
        socket_t * sClient = socket_new();
        socket_connectByHostName(sClient, "pb-homework.appspot.com");

        char request[200] = "";
        strcat(request, "GET /test/var/20?format=json HTTP/1.1\r\nHost:pb-homework.appspot.com\r\n\r\n");

        socket_write_string(sClient, request);
        socket_read(sClient, textServer, sizeof(textServer));
        http_request_t request = http_request_parse(textServer);
        request->form

        entity_t * entity = malloc(sizeof(struct entity_s));
        time_t time = ctime(NULL);
        strftime(entity->time, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
        strcat(pageText, entity->time);
        free(entity);

        socket_free(sClient);
        lib_free();

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

                // ���������� ������ �����
                fseek(file , 0 , SEEK_END);  // ������������� ������� � ����� �����
                long lSize = ftell(file);    // �������� ������ � ������
                rewind(file);                // ������������� ��������� � ����� �����

                char * buff = (char *) malloc(sizeof(char) * lSize); // �������� ������ ��� �������� ����������� �����
                fread(buff, 1, lSize, file);  // ��������� ���� � �����


                int l = 0;
                char pageText[10240] = "";
                char * punctuation = ".,:;!?";

                for(int i = 0; i < strlen(buff); i++)
                {
                    for(int j = 0; j < strlen(punctuation); j++)
                    {
                        if(buff[i] == punctuation[j])
                        {
                            pageText[l] = buff[i];
                            l++;
                        }
                    }
                }
                pageText[l] = '\0';

                char * text = textToJSON(pageText);
                strcat(buffer, text);
                free(text);
                free(buff);
                fclose(file);
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
