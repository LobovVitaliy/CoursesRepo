#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ScrumMaster.h"

struct ScrumMaster
{
    char name[20];
    char surname[20];
    char date[11];
    int count;
    double score;
};

master * master_new(void)
{
    return malloc(sizeof(struct ScrumMaster));
}

void master_free(master * self)
{
    free(self);
}

void master_set(master * self, char * name, char * surname, char * date, int count, double score)
{
    strcpy(self->name, name);
    strcpy(self->surname, surname);
    strcpy(self->date, date);
    self->count = count;
    self->score = score;
}

void master_swap(master * self, master * selfSwap)
{
    strcpy(self->name, selfSwap->name);
    strcpy(self->surname, selfSwap->surname);
    strcpy(self->date, selfSwap->date);
    self->count = selfSwap->count;
    self->score = selfSwap->score;
}

char * master_toJSON(master * self, int check)
{
    cJSON * SM = cJSON_CreateObject();
    cJSON_AddItemToObject(SM, "name", cJSON_CreateString(self->name));
    cJSON_AddItemToObject(SM, "surname", cJSON_CreateString(self->surname));
    cJSON_AddItemToObject(SM, "date", cJSON_CreateString(self->date));
    cJSON_AddItemToObject(SM, "count", cJSON_CreateNumber(self->count));
    cJSON_AddItemToObject(SM, "score", cJSON_CreateNumber(self->score));
    char * jsonSM = cJSON_Print(SM);
    return jsonSM;
}

char * master_toHTML(master * self, int ID)
{
    char * text = malloc(sizeof(char) * 10240);

    char pageText[1024] = "";
    sprintf(pageText,
            "<p>"
            "Name: %s<br>"
            "Surname: %s<br>"
            "Date: %s<br>"
            "Count: %i<br>"
            "Score: %.1f"
            "</p>",
            self->name, self->surname, self->date,
            self->count, self->score);
    strcat(text, pageText);

    char * pageTextLink = "<a href=\"#\" onclick=\"doDelete()\"/>Delete Scrum Master<br><br></a>\n";
    strcat(text, pageTextLink);

    char pageTextScript[1024];
    sprintf(pageTextScript,
                "<script>"
                "function doDelete() {"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/ScrumMasters/%i\", true);"
                "xhttp.send();"
                "}"
                "</script>", ID);
    strcat(text, pageTextScript);

    return text;
}


char * getName(master * self)
{
    return self->name;
}

char * getSurname(master * self)
{
    return self->surname;
}

