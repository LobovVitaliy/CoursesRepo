#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"
#include "parse.h"
#include "server.h"

int main()
{
    lib_init();

    socket_t * serverSocket = socket_new();

    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);

    master * scrumMaster[3];

    for (int i = 0; i < 3; i++)
        scrumMaster[i] = master_new();

    parse(scrumMaster, "ScrumMaster.xml");

    while(1) {
        socket_t * clientSocket = socket_accept(serverSocket);
        char buf[102400];

        if(socket_read(clientSocket, buf, 102400) == 0) {
            socket_close(clientSocket);
            socket_free(clientSocket);
            puts("Skipping empty request");
            continue;
        }

        http_request_t req = http_request_parse(buf);

        server_reply(clientSocket, req, scrumMaster);

        socket_close(clientSocket);
        socket_free(clientSocket);
    }

    for (int i = 0; i < 3; i++)
        master_free(scrumMaster[i]);

    socket_close(serverSocket);
    socket_free(serverSocket);
    lib_free();
    return 0;
}
