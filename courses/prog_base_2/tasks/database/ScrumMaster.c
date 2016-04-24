#include <stdlib.h>
#include <stdio.h>

#include "ScrumMaster.h"

void master_print(master_t * self) {
    printf("Name: %s\nSurname: %s\nCountS: %i\nCountF: %i\nScore: %.1f\nDate: %s\n\n",
        self->name, self->surname, self->countS, self->countF, self->score, self->date);
}

void master_printList(master_t * self, int size) {
    for (int i = 0; i < size; i++) {
        master_print(&self[i]);
    }
}

void master_set(master_t * self, char * name, char * surname, int countS, int countF, char * date, double score) {
    strcpy(self->name, name);
    strcpy(self->surname, surname);
    self->countS = countS;
    self->countF = countF;
    strcpy(self->date, date);
    self->score = score;
}

void masterList_set(master_t * self, master_t * sm) {
    strcpy(self->name, sm->name);
    strcpy(self->surname, sm->surname);
    self->countS = sm->countS;
    self->countF = sm->countF;
    strcpy(self->date, sm->date);
    self->score = sm->score;
}
