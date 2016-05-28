#include <winsock2.h>
#include "socket.h"

#pragma comment(lib,"ws2_32.lib")  // Winsock Library

struct socket_s {
    SOCKET winsock;
};

static socket_t * socket_new_winsock(SOCKET winsocket) {
    socket_t * self = malloc(sizeof(struct socket_s));
    self->winsock = winsocket;
    return self;
}

static SOCKADDR_IN getSockAddr(const char * host_name) {
    struct hostent * remoteHost = gethostbyname(host_name);
    char * ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
    SOCKADDR_IN recvSockAddr;

    memset(&recvSockAddr, 0, sizeof(recvSockAddr));     // zero the sockaddr_in structure
    recvSockAddr.sin_port = htons(80);                // specify the port portion of the address
    recvSockAddr.sin_family = AF_INET;                  // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr = inet_addr(ip);       // specify ip address

    return recvSockAddr;
}

socket_t * socket_new(void) {
    SOCKET winsock = socket(AF_INET, SOCK_STREAM, 0);
    // == INVALID_SOCKET; WSAGetLastError()
    socket_t * self = socket_new_winsock(winsock);
    return self;
}

void socket_free(socket_t * self) {
    closesocket(self->winsock);
    free(self);
}

const char * socket_getIPAddress(socket_t * self) {
    return "(null)";  // @todo
}

int socket_getPortNumber(socket_t * self) {
    return -1;  // @todo
}

int socket_bind(socket_t * self, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = bind(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo == SOCKET_ERROR
    return status;
}

int socket_listen(socket_t * self) {
    listen(self->winsock, 10);  // @todo param
    return 0; // @todo ?
}

socket_t * socket_accept(socket_t * self) {
    struct sockaddr_in clientaddr;
    int size = sizeof(struct sockaddr_in);
    SOCKET winsock = accept(self->winsock, (struct sockaddr *)&clientaddr, &size);
    if (INVALID_SOCKET == winsock) {
        return NULL;
    }
    socket_t * socket = socket_new_winsock(winsock);
    return socket;
}

int socket_connect(socket_t * self, const char * ipaddress, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = inet_addr(ipaddress),
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = connect(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo if < 0
    return status;
}

int socket_read(socket_t * self, char * recvBuff, int recvBuffSize) {
    int recvSize = recv(self->winsock, recvBuff, recvBuffSize, 0);
    // @todo == SOCKET_ERROR
    recvBuff[recvSize] = '\0';
    return recvSize;
}

int socket_write(socket_t * self, const char * msg, int msgSize) {
    int status = send(self->winsock, msg, msgSize, 0);
    // @todo < 0
    return status;
}

int socket_write_string(socket_t * self, const char * msg) {
    return socket_write(self, msg, strlen(msg));
}

void socket_close(socket_t * self) {
    closesocket(self->winsock);
}

void socket_connectByHostName(socket_t * self, const char * host_name) {
    SOCKADDR_IN recvSockAddr = getSockAddr(host_name);
    if(connect(self->winsock, (SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        puts("ERROR: socket could not connect");
        closesocket(self->winsock);
        WSACleanup();
        return;
    }
}

/* STATIC */

static WSADATA wsa;

void lib_init(void) {
    WSAStartup(MAKEWORD(2, 2), &wsa);
    // @todo check status != 0
}

void lib_free(void) {
    WSACleanup();
}
