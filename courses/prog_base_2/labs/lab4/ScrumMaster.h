#ifndef SCRUMMASTER_H_INCLUDED
#define SCRUMMASTER_H_INCLUDED

typedef struct ScrumMaster master;

master * master_new(void);
void master_free(master * self);

void master_set(master * self, char * name, char * surname, char * date, int count, double score);
void master_swap(master * self, master * selfSwap);
char * master_toJSON(master * self, int check);

char * getName(master * self);
char * getSurname(master * self);
char * getDate(master * self);
int getCount(master * self);
double getScore(master * self);

#endif
