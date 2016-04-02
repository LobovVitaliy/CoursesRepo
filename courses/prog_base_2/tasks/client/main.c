#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480

SOCKET Create_socket();
void Connect(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
SOCKADDR_IN getSockAddr(const char * host_name);
void Send(SOCKET recvSocket, const char * host_name, char * additional_string);
void SendResult(SOCKET recvSocket, const char * host_name, char * buffer);
void Receieve(SOCKET recvSocket, char * buffer);
char * offset(char * buffer);
char * findSum(char * string);


int main(void) {
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;

    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    char bufferResult[MAXBUFLEN];

    memset(buffer, 0, MAXBUFLEN);
    memset(bufferResult, 0, MAXBUFLEN);

    // Initialize Windows Socket DLL
    if(WSAStartup(MAKEWORD(2, 2), &Data) != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\n");
        return 0;
    }

    recvSockAddr = getSockAddr(host_name);

	recvSocket = Create_socket();                   // Create socket
    Connect(recvSocket, recvSockAddr);              // Connect

    Send(recvSocket, host_name, NULL);              // Send request
	Receieve(recvSocket, buffer);                   // Receieve

    Send(recvSocket, host_name, offset(buffer));    // Send request
    Receieve(recvSocket, buffer);                   // Receieve

    SendResult(recvSocket, host_name, buffer);      // Send request
    Receieve(recvSocket, bufferResult);             // Receieve

    printf("%s\n\n", bufferResult);

    system("pause");
    return 0;
}


SOCKET Create_socket() {
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

void Connect(SOCKET recvSocket, SOCKADDR_IN recvSockAddr) {
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\n");
        closesocket(recvSocket);
        WSACleanup();
        return;
    }
}

SOCKADDR_IN getSockAddr(const char * host_name) {
    struct hostent * remoteHost = gethostbyname(host_name);
    char * ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
    SOCKADDR_IN recvSockAddr;

    memset(&recvSockAddr, 0, sizeof(recvSockAddr));     // zero the sockaddr_in structure
    recvSockAddr.sin_port = htons(PORT);                // specify the port portion of the address
    recvSockAddr.sin_family = AF_INET;                  // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr = inet_addr(ip);       // specify ip address

    return recvSockAddr;
}

void Send(SOCKET recvSocket, const char * host_name, char * additional_string) {
    char request[200];

    if(additional_string == NULL)
        sprintf(request, "GET /var/11 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);
    else
        sprintf(request, "GET /var/11?%s HTTP/1.1\r\nHost:%s\r\n\r\n", additional_string, host_name);

    send(recvSocket, request, strlen(request), 0);
}

void SendResult(SOCKET recvSocket, const char * host_name, char * buffer) {
    char request[200];
    char result[100];

	sprintf(result, "result=%s", findSum(offset(buffer)));
	sprintf(request, "POST /var/11 HTTP/1.1\r\nHost: %s\r\nContent-length: %d\r\n\r\n%s\r\n", host_name, strlen(result), result);
	send(recvSocket, request, strlen(request), 0);
}

void Receieve(SOCKET recvSocket, char * buffer) {
    int status;
    if (recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET) == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\n");
        system("pause");
        return;
    }
}

char * offset(char * buffer) {
    char * string = strstr(buffer, "Content-Length") + 16;
    int size = atoi(string);
    int number = size;
    int i = 0;

    while (number > 9) {
        number /= 10;
        i++;
    }
    return string += i+5;
}

char * findSum(char * string) {

    char * number;
    int sum = 0;

    number = strtok(string, " ");
    sum += atoi(string);

    do {
        number = strtok('\0', ", ");
        sum += atoi(number);

    } while(number);

    sprintf(string, "%i", sum);
    return string;
}
