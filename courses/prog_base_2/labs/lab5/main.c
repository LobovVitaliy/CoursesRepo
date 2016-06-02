#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000

#include "server.h"
#include "db_manager.h"

int main()
{
    lib_init();
    printf("PORT: %i\n\n", PORT);
    socket_t * server = socket_new();
    socket_bind(server, PORT);
    socket_listen(server);

    char buffer[10000];
    socket_t * client = NULL;

    // работа с базой данных
    const char * dbFile = "ScrumMaster.db";
    db_t * db = db_new(dbFile);
    // работа с базой данных

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
            else if (strcmp(request.uri, "/api/ScrumMasters") == 0)  // else if (strncmp(request.uri, "/api/ScrumMasters?", 18) == 0)
            {
                server_masters(client, &request, db);
            }
            else if (strncmp(request.uri, "/api/ScrumMasters/", 18) == 0)
            {
                server_mastersByID(client, &request, db);
            }
            else if (strcmp(request.uri, "/ScrumMasters") == 0)
            {
                server_mastersHtml(client, &request, db);
            }
            else if (strncmp(request.uri, "/ScrumMasters/", 14) == 0)
            {
                server_mastersHtmlByID(client, &request, db);
            }
            else if (strcmp(request.uri, "/new-ScrumMaster") == 0)
            {
                server_mastersHtmlPOST(client, &request, db);
            }
            else
            {
                server_notFound(client);
            }
        }
    }

    db_free(db);
    socket_free(client);
    socket_free(server);
    lib_free();
    return 0;
}
