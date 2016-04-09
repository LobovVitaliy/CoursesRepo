#ifndef PLURAL_H_INCLUDED
#define PLURAL_H_INCLUDED

typedef struct ScrumMaster master;

master * master_new(void);
void master_free(master * self);
void master_print(master * self);

void master_set(master * self, char * name, char * surname, char * company, int year, char * date, int count, double score);
void team_set(master * self, char * nameTeam, char * nameProject, int i);

#endif
