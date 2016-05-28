#ifndef SCRUMMASTER_H_INCLUDED
#define SCRUMMASTER_H_INCLUDED

typedef struct ScrumMaster master_t;

master_t * master_new(void);
void master_free(master_t * self);

void master_print(master_t * self);
void master_printList(master_t * self, int size);
void master_set(master_t * self, int id, char * name, char * surname, int count, char * date, double score);
void masterList_set(master_t * self, master_t * sm);

#endif // SCRUMMASTER_H_INCLUDED

