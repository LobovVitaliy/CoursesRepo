#ifndef SCRUMMASTER_H_INCLUDED
#define SCRUMMASTER_H_INCLUDED

typedef struct ScrumMaster master_t;

master_t * master_new(void);
void master_free(master_t * self);

void master_set(master_t * self, int id, char * name, char * surname, int count, char * date, double score);

char * master_getName(master_t * self);
char * master_getSurname(master_t * self);
char * master_getDate(master_t * self);
int master_getCount(master_t * self);
double master_getScore(master_t * self);

#endif // SCRUMMASTER_H_INCLUDED

