#include <io.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    char client_reply[10000];
    char server_send[10000];
    int size = sizeof(struct sockaddr_in);


    puts("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    puts("Initialised.");

    //Create a socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    puts("Socket created.");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    //Bind
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    //Listen to incoming connections
    listen(s, 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    if ((new_socket = accept(s, (struct sockaddr *)&client, &size)) != INVALID_SOCKET )
    {
        puts("Connection accepted");
    }

    while(strcmp(client_reply, "EXIT") != 0)
    {
        int count = recv(new_socket, client_reply, 10000, 0);
        client_reply[count] = '\0';

        fflush(stdout);
        puts(client_reply);
        fflush(stdin);

        processing(client_reply, new_socket);

        //gets(server_send);
        //send(new_socket, server_send, strlen(server_send), 0);
    }

    if (new_socket == INVALID_SOCKET)
    {
        printf("Accept failed with error code : %d", WSAGetLastError());
        return 1;
    }

    closesocket(new_socket);
    closesocket(s);
    WSACleanup();

    return 0;
}

void processing(char * client_reply, SOCKET new_socket)
{
    char * message = "";
    char * item = "";
    int id = 0;
    int sizeMessage = strlen(client_reply);

    if (strncmp(client_reply, "GET /", 5) == 0)
    {
        message = strchr(client_reply, '/') + 1;
        message = strtok(message, " ");

        if (strlen(message) == sizeMessage - 5)
        {
            if ((item = strchr(message, '/')) == NULL)
            {
                printf("item = %s", message);
            }
            else
            {
                item++;
                int check = 0;

                message = strtok(message, "/");
                for (int i = 0; i < strlen(item); i++)
                {
                    if (!isdigit(item[i]))
                        check++;
                }
                if (check == 0)
                {
                    id = atoi(item);
                    printf("item = %s, id = %i\n", message, id);
                    send(new_socket, "OK", strlen("OK"), 0);
                }
                else
                    send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);//puts("YOU ARE LOOSER");
            }
        }
        else
            send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);//puts("YOU ARE LOOSER");
    }
    else if (strncmp(client_reply, "DELETE /", 8) == 0)
    {
        message = strchr(client_reply, '/') + 1;
        message = strtok(message, " ");

        if (strlen(message) == sizeMessage - 8)
        {
            if ((item = strchr(message, '/')) == NULL)
            {
                send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);
            }
            else
            {
                item++;
                int check = 0;

                message = strtok(message, "/");
                for (int i = 0; i < strlen(item); i++)
                {
                    if (!isdigit(item[i]))
                        check++;
                }
                if (check == 0)
                {
                    id = atoi(item);
                    printf("item = %s, id = %i\n", message, id);
                    send(new_socket, "OK", strlen("OK"), 0);
                }
                else
                    send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);//puts("YOU ARE LOOSER");
            }
        }
        else
            send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);//puts("YOU ARE LOOSER");
    }
    else if (strncmp(client_reply, "POST /", 6) == 0)
    {
        message = strchr(client_reply, '/') + 1;
        message = strtok(message, " ");

        if (strlen(message) == sizeMessage - 6)
        {
            if ((item = strchr(message, '/')) == NULL)
            {
                send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);
            }
            else
            {
                item++;
                int check = 0;

                message = strtok(message, "/");
                for (int i = 0; i < strlen(item); i++)
                {
                    if (!isdigit(item[i]))
                        check++;
                }
                if (check == 0)
                {
                    id = atoi(item);
                    printf("item = %s, id = %i\n", message, id);
                    postItemsID(new_socket);
                }
                else
                    send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);//puts("YOU ARE LOOSER");
            }
        }
        else
            send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);//puts("YOU ARE LOOSER");
    }
    else
    {
         send(new_socket, "YOU ARE LOOSER", strlen("YOU ARE LOOSER"), 0);//puts("YOU ARE LOOSER");
    }
}

void getItems ()
{

}

void getItemsID ()
{

}

void deleteItemsID ()
{

}

void postItemsID (SOCKET new_socket)
{
    char info[50];
    int countInfo = 0;

    char * name;
    char * surname;
    char * company;
    char * year;
    char * date;
    char * count;
    char * score;

    char * nameTeam;
    char * nameProject;

    do
    {
        if (countInfo > 20)
            send(new_socket, "Error\nScrum Master name:", strlen("Error\nScrum Master name:"), 0);
        else
            send(new_socket, "Scrum Master name:", strlen("Scrum Master name:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';
        printf("countIfo %i", countInfo);
        name = info;
    }
    while (countInfo > 20);

    countInfo = 0;
    puts(name);

    do
    {
        if (countInfo > 20)
            send(new_socket, "Error\nScrum Master surname:", strlen("Error\nScrum Master surname:"), 0);
        else
            send(new_socket, "Scrum Master surname:", strlen("Scrum Master surname:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        surname = info;
    }
    while (countInfo > 20);

    countInfo = 0;
    puts(surname);

    do
    {
        if (countInfo > 20)
            send(new_socket, "Error\nCompany name:", strlen("Error\nCompany name:"), 0);
        else
            send(new_socket, "Company name:", strlen("Company name:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        company = info;
    }
    while (countInfo > 20);

    countInfo = 0;
    puts(company);

    do
    {
        if (countInfo > 4)
            send(new_socket, "Error\nYear:", strlen("Error\nYear:"), 0);
        else
            send(new_socket, "Year:", strlen("Year:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        year = info;
    }
    while (countInfo > 4);

    countInfo = 0;
    puts(year);

    do
    {
        if (countInfo > 10)
            send(new_socket, "Error\nDate:", strlen("Error\nDate:"), 0);
        else
            send(new_socket, "Date:", strlen("Date:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        date = info;
    }
    while (countInfo > 10);

    countInfo = 0;
    puts(date);

    do
    {
        if (countInfo > 5)
            send(new_socket, "Error\nCount:", strlen("Error\nCount:"), 0);
        else
            send(new_socket, "Count:", strlen("Count:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        count = info;
    }
    while (countInfo > 5);

    countInfo = 0;
    puts(count);

    do
    {
        if (countInfo > 10)
            send(new_socket, "Error\nScore:", strlen("Error\nScore:"), 0);
        else
            send(new_socket, "Score:", strlen("Score:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        score = info;
    }
    while (countInfo > 10);

    countInfo = 0;
    puts(score);

    do
    {
        if (countInfo > 20)
            send(new_socket, "Error\nTeam name:", strlen("Error\nTeam name:"), 0);
        else
            send(new_socket, "Team name:", strlen("Team name:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        nameTeam = info;
    }
    while (countInfo > 20);

    countInfo = 0;
    puts(nameTeam);

    do
    {
        if (countInfo > 20)
            send(new_socket, "Error", strlen("Error"), 0);
        else
            send(new_socket, "Project name:", strlen("Project name:"), 0);

        countInfo = recv(new_socket, info, 50, 0);
        info[countInfo] = '\0';

        nameProject = info;
    }
    while (countInfo > 20);

    puts(nameProject);
}
