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

    char ** names = (char **) malloc(sizeof(char *) * 10);
	for (int i = 0; i < 10; i++)
    {
		names[i] = (char *) malloc(sizeof(char) * 50);
	}
    int countDB = db_name(db, names);
    // работа с базой данных

    puts("All databases:");
    for(int i = 0; i < countDB; i++) printf("%s\n", names[i]);
    puts("\n");

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
            else if (strcmp(request.uri, "/Database") == 0)
            {
                server_databases(client, &request, db, names, &countDB);
            }
            else if (strncmp(request.uri, "/Database/", 10) == 0)
            {
                server_databasesByID(client, &request, db, names, &countDB);
            }
            else if (strncmp(request.uri, "/new-Database/", 14) == 0)
            {
                server_databaseNew(client, &request, db, names, &countDB);
            }
            else if (strncmp(request.uri, "/up-Database/", 13) == 0)
            {
                server_databaseUpdate(client, &request, db, names, &countDB);
            }
            else
            {
                server_notFound(client);
            }
        }
    }

    // работа с базой данных
    for (int i = 0; i < 10; i++)
    {
		free(names[i]);
	}
	free(names);
    // работа с базой данных

    db_free(db);
    socket_free(client);
    socket_free(server);
    lib_free();
    return 0;
}
