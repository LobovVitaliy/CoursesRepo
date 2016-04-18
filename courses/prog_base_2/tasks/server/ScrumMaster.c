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
    struct Team team;
};

master * master_new(void) {
    return malloc(sizeof(struct ScrumMaster));
}

void master_free(master * self) {
    free(self);
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

void team_set(master * self, char * nameTeam, char * nameProject){
    self->team.nameTeam = nameTeam;
    self->team.nameProject = nameProject;
}


char * getName(master * self) {
    return self->name;
}

char * getSurname(master * self) {
    return self->surname;
}

char * getCompany(master * self) {
    return self->company;
}

int getYear(master * self) {
    return self->year;
}

char * getDate(master * self) {
    return self->date;
}

int getCount(master * self) {
    return self->count;
}

double getScore(master * self) {
    return self->score;
}

char * getNameTeam(master * self) {
    return self->team.nameTeam;
}

char * getNameProject(master * self) {
    return self->team.nameProject;
}
