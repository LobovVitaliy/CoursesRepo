#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define NO_FLAGS_SET 0
#define MAXBUFLEN 20480

SOCKET Create_socket();
void Connect(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
SOCKADDR_IN getSockAddr();

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char server_reply[10000];
    char client_send[10000];


    puts("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    puts("Initialised.");

    //Create a socket
    if((s = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    puts("Socket created.");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    //Connect to remote server
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("Connect error!");
        return 1;
    }
    puts("Connected");

    do
    {
        gets(client_send);
        send(s, client_send, strlen(client_send), 0);

        int count = recv(s, server_reply, 10000, 0);
        server_reply[count] = '\0';

        fflush(stdout);
        puts(server_reply);
        fflush(stdin);
    }
    while(strcmp(client_send, "EXIT") != 0);

    closesocket(s);
    WSACleanup();

    return 0;
}


SOCKET Create_socket()
{
    SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(recvSocket == INVALID_SOCKET)
    {
        printf("ERROR: socket unsuccessful\n");
        WSACleanup();
        system("pause");
        return 0;
    }
    return recvSocket;
}

void Connect(SOCKET recvSocket, SOCKADDR_IN recvSockAddr)
{
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\n");
        closesocket(recvSocket);
        WSACleanup();
        return;
    }
}

SOCKADDR_IN getSockAddr()
{
    SOCKADDR_IN recvSockAddr;

    memset(&recvSockAddr, 0, sizeof(recvSockAddr));     // zero the sockaddr_in structure
    recvSockAddr.sin_port = htons(8888);                // specify the port portion of the address
    recvSockAddr.sin_family = AF_INET;                  // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    return recvSockAddr;
}
