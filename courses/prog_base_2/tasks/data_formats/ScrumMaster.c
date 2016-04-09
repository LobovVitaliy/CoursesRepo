#include <stdio.h>
#include "ScrumMaster.h"

struct Team {
    char * nameTeam;
    char * nameProject;
};

struct ScrumMaster {
    char * name;
    char * surname;
    char * company;
    int year;
    char * date;
    int count;
    double score;
    struct Team team[2];
};

master * master_new(void) {
    return malloc(sizeof(struct ScrumMaster));
}

void master_free(master * self) {
    free(self);
}

void master_print(master * self) {
    printf("Name: %s\nSurname: %s\nCompany: %s\nYear: %i\nDate: %s\nCount: %i\nScore: %.2f\n", self->name, self->surname, self->company, self->year, self->date, self->count, self->score);
    for(int i = 0; i < 2; i++) {
        printf("   NameTeam: %s\n   NameProject: %s\n\n", self->team[i].nameTeam, self->team[i].nameProject);
    }
}

void master_set(master * self, char * name, char * surname, char * company, int year, char * date, int count, double score){
    self->name = name;
    self->surname = surname;
    self->company = company;
    self->year = year;
    self->date = date;
    self->count = count;
    self->score = score;
}

void team_set(master * self, char * nameTeam, char * nameProject, int i){
    self->team[i].nameTeam = nameTeam;
    self->team[i].nameProject = nameProject;
}
