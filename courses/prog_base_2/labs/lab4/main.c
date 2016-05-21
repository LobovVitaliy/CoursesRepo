#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "server.h"

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

        if(strlen(buffer) != 0)
        {
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
            else if (strncmp(request.uri, "/ScrumMasters/", 14) == 0)
            {
                server_mastersHtmlByID(client, &request, ScrumMasters, &size);
            }
            else if (strcmp(request.uri, "/new-ScrumMaster") == 0)
            {
                server_mastersHtmlPOST(client, &request, ScrumMasters, &size);
            }
            else
            {
                server_notFound(client);
            }
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
