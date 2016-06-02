#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ScrumMaster.h"

struct ScrumMaster
{
    int id;
    char name[20];
    char surname[20];
    int countK;
    int countP;
};

master_t * master_new(void)
{
    return malloc(sizeof(struct ScrumMaster));
}

void master_free(master_t * self)
{
    free(self);
}

void master_set(master_t * self, int id, char * name, char * surname, int countK, int countP)
{
    self->id = id;
    strcpy(self->name, name);
    strcpy(self->surname, surname);
    self->countK = countK;
    self->countP = countP;
}

int master_getID(master_t * self)
{
    return self->id;
}

char * master_getName(master_t * self)
{
    return self->name;
}

char * master_getSurname(master_t * self)
{
    return self->surname;
}

int master_getCountK(master_t * self)
{
    return self->countK;
}

int master_getCountP(master_t * self)
{
    return self->countP;
}
