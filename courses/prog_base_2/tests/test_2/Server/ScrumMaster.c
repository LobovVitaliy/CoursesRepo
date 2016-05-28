#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ScrumMaster.h"

struct ScrumMaster {
    int id;
    char name[256];
    char surname[256];
    int count;
    double score;
    char date[11];
};

master_t * master_new(void) {
    return malloc(sizeof(struct ScrumMaster));
}

void master_free(master_t * self) {
    free(self);
}

void master_set(master_t * self, int id, char * name, char * surname, int count, char * date, double score) {
    self->id = id;
    strcpy(self->name, name);
    strcpy(self->surname, surname);
    self->count = count;
    strcpy(self->date, date);
    self->score = score;
}


char * master_getName(master_t * self)
{
    return self->name;
}

/*char * entity_getName(entity_t * self)
{
    return self->name;
}

char * entity_getSurname(entity_t * self)
{
    return self->surname;
}*/
