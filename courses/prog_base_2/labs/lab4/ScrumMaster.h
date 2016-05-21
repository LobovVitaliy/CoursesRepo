#ifndef SCRUMMASTER_H_INCLUDED
#define SCRUMMASTER_H_INCLUDED

#include "cJSON.h"

typedef struct ScrumMaster master;

master * master_new(void);
void master_free(master * self);

void master_set(master * self, char * name, char * surname, char * date, int count, double score);
void master_swap(master * self, master * selfSwap);

char * master_toJSON(master * self, int check);
char * master_toHTML(master * self, int ID);

char * getName(master * self);
char * getSurname(master * self);

#endif
