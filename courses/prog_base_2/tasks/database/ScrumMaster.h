#ifndef SCRUMMASTER_H_INCLUDED
#define SCRUMMASTER_H_INCLUDED

typedef struct ScrumMaster {
    int id;
    char name[256];
    char surname[256];
    int countS;
    int countF;
    double score;
    char date[11];
} master_t;

void master_print(master_t * self);
void master_printList(master_t * self, int size);
void master_set(master_t * self, char * name, char * surname, int countS, int countF, char * date, double score);
void masterList_set(master_t * self, master_t * sm);

#endif // SCRUMMASTER_H_INCLUDED
