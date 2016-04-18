#include "server.h"
#include <stdio.h>
#include <stddef.h>  // ptrdiff_t

void server_reply(socket_t * clientSocket, http_request_t req, master ** scrumMaster)
{
    if (strcmp(req.uri, "/ScrumMasters") == 0)
    {
        if (strcmp(req.method, "GET") == 0)
        {
            getItems(clientSocket, scrumMaster);
        }
        else
            error(clientSocket, "Not found!");
    }
    else if (strncmp(req.uri, "/ScrumMasters/", 14) == 0)
    {
        int id = 0;
        if ((id = findIndex(req)) >= 0 && id < 3)
        {
            if (strcmp(req.method, "GET") == 0)
            {
                getItemsID(clientSocket, scrumMaster[id]);
            }
            else if (strcmp(req.method, "DELETE") == 0)
            {
                deleteItemsID(clientSocket, scrumMaster[id]);
            }
            else if (strcmp(req.method, "POST") == 0)
            {
                postItemsID(clientSocket, req, scrumMaster[id]);
            }
            else
                error(clientSocket, "Not found!");
        }
        else
               error(clientSocket, "Incorrect ID");
    }
    else
        error(clientSocket, "Not found!");
}

void error(socket_t * clientSocket, char * str)
{
    char buffer[10000] = "";
    char text[10000] = "";

    sprintf(text, "<Error>%s</Error>\n", str);

    sprintf(buffer,
            "\nHTTP/1.1 200 OK\n"
            "Content-Type: text/xml\n"
            "Content-Length: %i\n"
            "\n%s", strlen(text), text
           );

    socket_write_string(clientSocket, buffer);
}

void getItems(socket_t * clientSocket, master ** scrumMaster)
{
    char buffer[10000] = "";
    char text[10000] = "";

    strcat(text, "<ScrumMasters>\n");

    for (int i = 0; i < 3; i++)
    {
        sprintf(buffer, "   <ScrumMaster>\n      "
                "<name>%s</name>\n      "
                "<surname>%s</surname>\n      "
                "<company year=""%i"">%s</company>\n      "
                "<date>%s</date>\n      "
                "<count>%i</count>\n      "
                "<score>%.1f</score>\n      "
                "<teams>\n         "
                "<team>\n            "
                "<nameTeam>%s</nameTeam>\n            "
                "<nameProject>%s</nameProject>\n         "
                "</team>\n      "
                "</teams>\n   "
                "</ScrumMaster>\n",
                getName(scrumMaster[i]), getSurname(scrumMaster[i]), getYear(scrumMaster[i]),
                getCompany(scrumMaster[i]), getDate(scrumMaster[i]), getCount(scrumMaster[i]), getScore(scrumMaster[i]),
                getNameTeam(scrumMaster[i]), getNameProject(scrumMaster[i])
                );
        strcat(text, buffer);
    }

    strcat(text, "</ScrumMasters>\n");

    sprintf(buffer,
            "\nHTTP/1.1 200 OK\n"
            "Content-Type: text/xml\n"
            "Content-Length: %i\n"
            "\n%s", strlen(text), text
           );

    socket_write_string(clientSocket, buffer);
}

void getItemsID(socket_t * clientSocket, master * scrumMaster)
{
    char buffer[10000] = "";
    char text[10000] = "";

    sprintf(buffer, "   <ScrumMaster>\n      "
            "<name>%s</name>\n      "
            "<surname>%s</surname>\n      "
            "<company year=""%i"">%s</company>\n      "
            "<date>%s</date>\n      "
            "<count>%i</count>\n      "
            "<score>%.1f</score>\n      "
            "<teams>\n         "
            "<team>\n            "
            "<nameTeam>%s</nameTeam>\n            "
            "<nameProject>%s</nameProject>\n         "
            "</team>\n      "
            "</teams>\n   "
            "</ScrumMaster>\n",
            getName(scrumMaster), getSurname(scrumMaster), getYear(scrumMaster),
            getCompany(scrumMaster), getDate(scrumMaster), getCount(scrumMaster), getScore(scrumMaster),
            getNameTeam(scrumMaster), getNameProject(scrumMaster)
            );
    strcat(text, buffer);

    sprintf(buffer,
            "\nHTTP/1.1 200 OK\n"
            "Content-Type: text/xml\n"
            "Content-Length: %i\n"
            "\n%s", strlen(text), text
           );

    socket_write_string(clientSocket, buffer);
}

void deleteItemsID(socket_t * clientSocket, master * scrumMaster)
{
    char buffer[10000] = "";

    master_set(scrumMaster, NULL, NULL, NULL, NULL, NULL, NULL, 0);
    team_set(scrumMaster, NULL, NULL);

    sprintf(buffer,
            "\nHTTP/1.1 200 OK\n"
            "Content-Type: text/xml\n"
            "Content-Length: %i\n"
            "\n%s\n", strlen("Successfully removed"), "Successfully removed"
           );

    socket_write_string(clientSocket, buffer);
}

void postItemsID(socket_t * clientSocket, http_request_t req, master * scrumMaster)
{
    const char * name = http_request_getArg(&req, "name");
    const char * surname = http_request_getArg(&req, "surname");
    const char * company = http_request_getArg(&req, "company");
    const char * year = http_request_getArg(&req, "year");
    const char * date = http_request_getArg(&req, "date");
    const char * count = http_request_getArg(&req, "count");
    const char * score = http_request_getArg(&req, "score");
    const char * nameTeam = http_request_getArg(&req, "nameTeam");
    const char * nameProject = http_request_getArg(&req, "nameProject");

    int checkNum = 0;
    // check year
    for (int i = 0; i < 4; i++)
    {
        if (!isdigit(year[i]))
            checkNum++;
    }
    // check date
    for (int i = 0; i < 4; i++)
    {
        if (!isdigit(date[i]))
            checkNum++;
    }
    if (date[4] != '-')
        checkNum++;
    for (int i = 5; i < 7; i++)
    {
        if (!isdigit(date[i]))
            checkNum++;
    }
    if (atoi(date + 5) > 12)
        checkNum++;
    if (date[7] != '-')
        checkNum++;
    for (int i = 8; i < 10; i++)
    {
        if (!isdigit(date[i]))
            checkNum++;
    }
    if (atoi(date + 8) > 31)
        checkNum++;
    // check count
    for (int i = 0; i < strlen(count); i++)
    {
        if (!isdigit(count[i]))
            checkNum++;
    }
    // check score
    int countDot = 0;
    for (int i = 0; i < strlen(score); i++)
    {
        if (!isdigit(score[i]) && score[i] != '.')
            checkNum++;
        if (score[i] == '.')
            countDot++;
    }
    if (countDot > 1)
        checkNum++;

    if (strlen(name) == 0 || strlen(surname) == 0 || strlen(company) == 0 || strlen(year) != 4 || strlen(date) != 10
        || strlen(count) == 0 || strlen(score) == 0 || strlen(nameTeam) == 0 || strlen(nameProject) == 0
        || strlen(name) > 25 || strlen(surname) > 25  || strlen(company) > 25 || strlen(count) > 5
        || strlen(score) > 5 || strlen(nameTeam) > 25 || strlen(nameProject) > 25
       )
       {
            checkNum++;
       }

    if (checkNum == 0)
    {
        master_set(scrumMaster, name, surname, company, atoi(year), date, atoi(count), atof(score));
        team_set(scrumMaster, nameTeam, nameProject);

        getItemsID(clientSocket, scrumMaster);
    }
    else
        error(clientSocket, "Not found!");
}


int findIndex (http_request_t req)
{
    char * id = req.uri + 14;
    int check = 0;

    for (int i = 0; i < strlen(req.uri) - 14; i++)
    {
        if (!isdigit(id[i]))
            check++;
    }
    if (check == 0)
        return atoi(id);
    else
        return -1;
}


http_request_t http_request_parse(const char * const request)
{
    http_request_t req;
    req.form = NULL;
    req.formLength = 0;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    // parse form data
    const char * bodyStartPtr = strstr(request, "\r\n\r\n") + strlen("\r\n\r\n");
    const char * cur = bodyStartPtr;
    const char * pairEndPtr = cur;
    const char * eqPtr = cur;
    while (strlen(cur) > 0) {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr) {
            pairEndPtr = cur + strlen(cur);
        }
        keyvalue_t kv;
        // get key
        eqPtr = strchr(cur, '=');
        ptrdiff_t keyLen = eqPtr - cur;
        memcpy(kv.key, cur, keyLen);
        kv.key[keyLen] = '\0';
        // get value
        eqPtr++;
        ptrdiff_t valueLen = pairEndPtr - eqPtr;
        memcpy(kv.value, eqPtr, valueLen);
        kv.value[valueLen] = '\0';
        // insert key-value pair into request form list
        req.formLength += 1;
        req.form = realloc(req.form, sizeof(keyvalue_t) * req.formLength);
        req.form[req.formLength - 1] = kv;
        cur = pairEndPtr + ((strlen(pairEndPtr) > 0) ? 1 : 0);
    }
    return req;
}

const char * http_request_getArg(http_request_t * self, const char * key)
{
    for (int i = 0; i < self->formLength; i++) {
        if (strcmp(self->form[i].key, key) == 0) {
            return self->form[i].value;
        }
    }
    return NULL;
}

const char * keyvalue_toString(keyvalue_t * self)
{
    char * str = malloc(sizeof(char) * (strlen(self->key) + strlen(self->value) + 2));
    sprintf(str, "%s=%s\0", self->key, self->value);
    return str;
}
