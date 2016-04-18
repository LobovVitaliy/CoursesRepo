#ifndef PLURAL_H_INCLUDED
#define PLURAL_H_INCLUDED

typedef struct ScrumMaster master;

master * master_new(void);
void master_free(master * self);
void master_print(master * self);

void master_set(master * self, char * name, char * surname, char * company, int year, char * date, int count, double score);
void team_set(master * self, char * nameTeam, char * nameProject);

char * getName(master * self);
char * getSurname(master * self);
char * getCompany(master * self);
int getYear(master * self);
char * getDate(master * self);
int getCount(master * self);
double getScore(master * self);
char * getNameTeam(master * self);
char * getNameProject(master * self);

#endif
