#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_manager.h"
#include "list.h"
#include "server.h"

int main()
{
    lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);

    char buffer[10240] = "";
    socket_t * client = NULL;

    const char * dbFile = "ScrumMaster.db";
    db_t * db = db_new(dbFile);

    list_t * master = list_new();

    while(1)
    {
        client = socket_accept(server);
        socket_read(client, buffer, sizeof(buffer));

        if(strlen(buffer) != 0)
        {
            printf(">> Got request:\n%s\n", buffer);
            http_request_t request = http_request_parse(buffer);

            if (strcmp(request.uri, "/info") == 0)
            {
                server_first(client, &request);
            }
            else if (strcmp(request.uri, "/external") == 0)
            {
                server_second(client, &request);
            }
            else if (strcmp(request.uri, "/database") == 0)
            {
                server_third(client, &request, db, master);
            }
            else if (strncmp(request.uri, "/files/", 7) == 0)
            {
                server_fourth(client, &request);
            }
            else
            {
                server_notFound(client);
            }
        }
    }

    socket_free(client);
    socket_free(server);
    list_free(master);
    db_free(db);
    lib_free();
    return 0;
}

