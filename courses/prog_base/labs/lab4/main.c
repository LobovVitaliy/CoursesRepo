#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

struct Robot {

    char name[100];
    char weapon[100];

    int health;
    int protection;
    int attack;

    int damage;
    int defense;

    int money;
};

enum ConsoleColor {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        Yellow = 14,
        White = 15
};

void Desert_Eagle();
void Awp();
void AK_47();
void Famas();
void M4a4();
void Helmet();
void Kevlar_Vest();
void window();
void clean();
void clean_result();
void clean_shop_left();
void clean_shop_right();
void POS(int x, int y, int color);
void loading();
void result(struct Robot robot[], struct Robot * pVar);
struct Robot * shop(struct Robot robot[], struct Robot * pVar);
struct Robot * Weapons(struct Robot robot[], struct Robot * pVar);
struct Robot * Other(struct Robot robot[], struct Robot * pVar);
void diagram (int x, int y);
void info(struct Robot robot[], struct Robot * pVar);
void Kuratas(struct Robot robot[], struct Robot * pVar);
void Scorpio(struct Robot robot[], struct Robot * pVar);
void Terminator(struct Robot robot[], struct Robot * pVar);
void Maxopo(struct Robot robot[], struct Robot * pVar);
struct Robot * unit(struct Robot robot[], struct Robot * pVar);
struct Robot * battle(struct Robot robot[], struct Robot * pVar, struct Robot * battle_pVar);
int vs(struct Robot * new_pVar, struct Robot * battle_pVar);
void save(struct Robot robot[], struct Robot * pVar, struct Robot * battle_pVar);
void download(struct Robot robot[], struct Robot * pVar, struct Robot * battle_pVar);

void Desert_Eagle() {

    srand(time(NULL));

    int color = rand()%15 + 1;
    int x,y;

    for (x=1; x<=29; x++)
        for (y=0; y<=15; y++) {

            POS(x+99,y+3,color);

            if ((x==3 || x==23 || x==24) && y==1)
                printf("#");
            if (x>=2 && x<=26 && y==2)
                printf("#");
            if (x>=1 && x<=28 && (y==3 || y==4 ))
                printf("#");
            if (x>=2 && x<=27 && y==5)
                printf("#");
            if (x>=3 && x<=28 && y==6)
                printf("#");
            if (x>=13 && x<=29 && y==7)
                printf("#");
            if (((x>=14 && x<=25) || (x>=20 && x<=27) || x==18) && y==8)
                printf("#");
            if ((x==15 || (x>=20 && x<=26) || x==18) && y==9)
                printf("#");
            if ((x==15 || (x>=20 && x<=26)) && y==10)
                printf("#");
            if ((x>=16 && x<=27) && y==11)
                printf("#");
            if ((x>=20 && x<=28) && (y==12 || y==13))
                printf("#");
            if ((x>=20 && x<=27) && y==14)
                printf("#");
            if ((x>=19 && x<=26) && y==15)
                printf("#");
    }
}

void Awp() {

    srand(time(NULL));

    int color = rand()%15 + 1;
    int x,y;

    for (x=1; x<=51; x++)
        for (y=1; y<=15; y++) {

            POS(x+88,y+3,color);

            if ((x==29 || x==30) && y==1)
                printf("#");
            if (((x>=27 && x<=32) || (x>=36 && x<=41)) && y==2)
                printf("#");
            if (x>=22 && x<=41 && (y==3 || y==4 ))
                printf("#");
            if (((x>=26 && x<=28) || (x>=31 && x<=33)) && y==5)
                printf("#");
            if (((x>=16 && x<=35) || x==2) && y==6)
                printf("#");
            if (x>=1 && x<=36 && y==7)
                printf("#");
            if (x>=1 && x<=51 && y==8)
                printf("#");
            if (x>=23 && x<=51 && y==9)
                printf("#");
            if (((x>=24 && x<=30) || (x>=34 && x<=44) || (x>=48 && x<=51)) && y==10)
                printf("#");
            if (((x>=25 && x<=37) || (x>=42 && x<=44) || (x>=48 && x<=51)) && y==11)
                printf("#");
            if (((x>=25 && x<=29) || (x>=34 && x<=37) || (x>=42 && x<=44) || (x>=49 && x<=51)) && y==12)
                printf("#");
            if (((x>=25 && x<=29) || (x>=35 && x<=51)) && y==13)
                printf("#");
            if (((x>=26 && x<=29) || (x>=35 && x<=50)) && y==14)
                printf("#");
            if ((x>=35 && x<=37) && y==15)
                printf("#");
        }
}

void AK_47() {

    srand(time(NULL));

    int color = rand()%15 + 1;
    int x,y;

    for (x=1; x<=55; x++)
        for (y=1; y<=14; y++) {

            POS(x+86,y+3,color);

            if ((x==2 || (x>=22 && x<=26)) && y==1)
                printf("#");
            if ((x==2 || x==3 || (x>=9 && x<=38)) && y==2)
                printf("#");
            if (((x>=1 && x<=8) || (x>=8 && x<=39)) && y==3)
                printf("#");
            if (x>=1 && x<=41 && y==4)
                printf("#");
            if (x>=13 && x<=52 && y==5)
                printf("#");
            if (x>=27 && x<=55 && y==6)
                printf("#");
            if (((x>=27 && x<=32) || (x>=36 && x<=39) || (x>=43 && x<=55)) && y==7)
                printf("#");
            if (((x>=26 && x<=39) || (x>=46 && x<=55)) && y==8)
                printf("#");
            if (((x>=25 && x<=30) || (x>=37 && x<=39) || (x>=49 && x<=55)) && y==9)
                printf("#");
            if (((x>=24 && x<=29) || (x>=37 && x<=40) || (x>=52 && x<=55)) && y==10)
                printf("#");
            if (((x>=23 && x<=28) || (x>=38 && x<=40)) && y==11)
                printf("#");
            if (((x>=22 && x<=27) || (x>=38 && x<=40)) && y==12)
                printf("#");
            if (x>=21 && x<=26 && y==13)
                printf("#");
            if (x>=21 && x<=25 && y==14)
                printf("#");
        }
}

void Famas() {

    srand(time(NULL));

    int color = rand()%15 + 1;
    int x,y;

    for (x=1; x<=49; x++)
        for (y=1; y<=18; y++) {

            POS(x+89,y+3,color);

            if (x>=17 && x<=34 && y==1)
                printf("#");
            if (((x>=16 && x<=17) || (x>=34 && x<=35)) && y==2)
                printf("#");
            if (((x>=15 && x<=16) || (x>=35 && x<=36)) && y==3)
                printf("#");
            if (((x>=14 && x<=15) || (x>=36 && x<=37)) && y==4)
                printf("#");
            if (((x>=13 && x<=39) || (x>=2 && x<=4)) && y==5)
                printf("#");
            if (x>=1 && x<=40 && y==6)
                printf("#");
            if (x>=1 && x<=48 && y==7)
                printf("#");
            if (x>=1 && x<=49 && (y==8 || y==9))
                printf("#");
            if (((x>=1 && x<=18) || (x>=23 && x<=27) || (x>=30 && x<=35)) && y==10)
                printf("#");
            if (((x>=1 && x<=2) || (x>=10 && x<=17) || (x>=22 && x<=34)) && y==11)
                printf("#");
            if ((x==1 || (x>=9 && x<=16) || (x>=21 && x<=25) || x==33) && y==12)
                printf("#");
            if (((x>=9 && x<=15) || (x>=20 && x<=24) || x==32) && y==13)
                printf("#");
            if (((x>=9 && x<=15) || (x>=19 && x<=23) || x==31) && y==14)
                printf("#");
            if (((x>=10 && x<=15) || (x>=19 && x<=30) || (x>=27 && x<=30)) && y==15)
                printf("#");
            if (x>=11 && x<=16 && y==16)
                printf("#");
            if (x>=12 && x<=17 && y==17)
                printf("#");
            if (x>=13 && x<=18 && y==18)
                printf("#");
        }
}

void M4a4() {

    srand(time(NULL));

    int color = rand()%15 + 1;
    int x,y;

    for (x=1; x<=55; x++)
        for (y=1; y<=15; y++) {

            POS(x+86,y+3,color);

            if (x==46 && y==1)
                printf("#");
            if (((x>=17 && x<=24) || (x>=45 && x<=46)) && y==2)
                printf("#");
            if (((x>=17 && x<=25) || (x>=44 && x<=46)) && y==3)
                printf("#");
            if (x>=2 && x<=55 && y==4)
                printf("#");
            if (x>=1 && x<=55 && y==5)
                printf("#");
            if (x>=1 && x<=44 && y==6)
                printf("#");
            if (x>=1 && x<=39 && y==7)
                printf("#");
            if (((x>=1 && x<=13) || (x>=17 && x<=25)) && y==8)
                printf("#");
            if (((x>=1 && x<=10) || (x>=17 && x<=19) || (x>=22 && x<=25)) && y==9)
                printf("#");
            if (((x>=1 && x<=6) || (x>=16 && x<=18) || (x>=22 && x<=25)) && y==10)
                printf("#");
            if (((x>=2 && x<=4) || (x>=15 && x<=17) || (x>=23 && x<=25)) && y==11)
                printf("#");
            if (((x>=14 && x<=16) || (x>=23 && x<=26)) && y==12)
                printf("#");
            if (x>=23 && x<=26 && y==13)
                printf("#");
            if (x>=24 && x<=26 && y==14)
                printf("#");
        }
}


void Helmet() {

    srand(time(NULL));

    int color = rand()%15 + 1;
    int x,y;

    for (x=1; x<=30; x++)
        for (y=1; y<=15; y++) {

            POS(x+105,y+3,color);

            if (x>=8 && x<=12 && y==1)
                printf("#");
            if (x>=6 && x<=14 && y==2)
                printf("#");
            if (x>=4 && x<=16 && y==3)
                printf("#");
            if (x>=3 && x<=17 && y==4)
                printf("#");
            if (x>=2 && x<=18 && y==5)
                printf("#");
            if (((x>=1 && x<=4) || (x>=14 && x<=19)) && y==6)
                printf("#");
            if (((x>=1 && x<=3) || (x>=15 && x<=19)) && y==7)
                printf("#");
            if ((x==2 || (x>=16 && x<=19)) && y==8)
                printf("#");
            if ((x==3 || (x>=16 && x<=18)) && y==9)
                printf("#");
            if ((x==4 || x==17) && y==10)
                printf("#");
            if ((x==5 || x==16) && y==11)
                printf("#");
            if ((x==6 || x==15) && y==12)
                printf("#");
        }
}

void Kevlar_Vest() {

    srand(time(NULL));

    int color = rand()%15 + 1;
    int x,y;

    for (x=1; x<=30; x++)
        for (y=1; y<=15; y++) {

            POS(x+101,y+3,color);

            if (((x>=8 && x<=9) || (x>=19 && x<=20)) && (y==1 || y==2))
                printf("#");
            if (((x>=8 && x<=10) || (x>=18 && x<=20)) && y==3)
                printf("#");
            if (((x>=8 && x<=11) || (x>=17 && x<=20)) && y==4)
                printf("#");
            if (x>=8 && x<=20 && y==5)
                printf("#");
            if (x>=7 && x<=21 && (y>=6 && y<=10))
                printf("#");
            if (x>=8 && x<=20 && y==11)
                printf("#");
        }
}


void window() {
    int x,y;

    for (x=50; x<149; x++)
        for (y=1; y<49; y++) {
            POS(x,y,DarkGray);
            if (x==50 || x==80 || x==148 || y==1 || y==48)
                printf("#");
    }
}

void clean() {
    int y;

    for (y=1; y<49; y++) {
        POS(50,y,DarkGray);
        puts("                                                                                                   ");
    }
}

void clean_result() {
    int y;

    for (y=25; y<46; y++) {
        POS(0,y,DarkGray);
        puts("                                                  ");
    }
}

void clean_shop_left() {
    int y;

    for (y=2; y<48; y++) {
        POS(51,y,DarkGray);
        puts("                             ");
    }
}

void clean_shop_right() {
    int y;

    for (y=2; y<48; y++) {
        POS(81,y,DarkGray);
        puts("                                                                   ");
    }
}

void POS(int x, int y, int color) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}

void loading() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i,d = 0;

    POS(127,43,Brown);
    puts("LOADING");
    for (i=0; i<30; i++) {
        POS(115+d,45,Black);
        SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
        puts(" ");
        Sleep(100);
        d+=1;
    }
    SetConsoleTextAttribute(hConsole, LightGray);
}

void result(struct Robot robot[], struct Robot * pVar) {

    POS(7,25,LightGreen);
    printf("Name:");
    POS(30,25,Brown);
    printf("%s\n", pVar->name);

    POS(7,30,LightRed);
    printf("Weapon:");
    POS(30,30,Brown);
    printf("%s", pVar->weapon);

    POS(7,35,LightMagenta);
    printf("Health:");
    POS(30,35,Brown);
    printf("%i", pVar->health);

    POS(7,40,LightCyan);
    printf("Protection:");
    POS(30,40,Brown);
    printf("%i", pVar->protection);

    POS(7,45,LightCyan);
    printf("Attack:");
    POS(30,45,Brown);
    printf("%i", pVar->attack);

    POS(33,45,Brown);
    printf("   +   %i", pVar->damage);

    POS(33,40,Brown);
    printf("   +   %i", pVar->defense);
}


struct Robot * shop(struct Robot robot[], struct Robot * pVar) {

    char com;
    int control_2 = 1;
    int check = 0;

    result(robot, pVar);

    POS(62,5,Yellow);
    puts("Оружие");

    POS(62,10,DarkGray);
    puts("Другое");

    POS(63,45,LightGreen);
    printf("$%i", pVar->money);

    while (check==0) {

        com = getch();
        switch (com) {
            case 'w': control_2--; break;
            case 's': control_2++; break;
        }

        switch (control_2) {
            case 1:     POS(62,5,Yellow);
                        puts("Оружие");

                        POS(62,10,DarkGray);
                        puts("Другое");
                    break;

            case 2:     POS(62,5,DarkGray);
                        puts("Оружие");

                        POS(62,10,Yellow);
                        puts("Другое");
                    break;

            default:    if (control_2 > 2) {
                            POS(62,5,Yellow);
                            puts("Оружие");

                            POS(62,10,DarkGray);
                            puts("Другое");
                            control_2 = 1;
                        }
                        else {
                            POS(62,5,DarkGray);
                            puts("Оружие");

                            POS(62,10,Yellow);
                            puts("Другое");
                            control_2 = 2;
                        }
                    break;
        }

        switch (com) {
            case 'd':   if (control_2==1) {
                            clean_shop_left();
                            pVar = Weapons(robot, pVar);

                            POS(62,5,Yellow);
                            puts("Оружие");

                            POS(62,10,DarkGray);
                            puts("Другое");

                            POS(63,45,LightGreen);
                            printf("$%i", pVar->money);
                        }
                        if (control_2==2) {
                            clean_shop_left();
                            pVar = Other(robot, pVar);

                            POS(62,5,DarkGray);
                            puts("Оружие");

                            POS(62,10,Yellow);
                            puts("Другое");

                            POS(63,45,LightGreen);
                            printf("$%i", pVar->money);
                        }
                        break;

            case 'a':   check = 1;
                        clean();
                        break;
        }
    }

    return pVar;
}

struct Robot * Weapons(struct Robot robot[], struct Robot * pVar) {

    char com;
    int control_3 = 1;
    int check = 0;

    struct Robot * new_pVar = pVar;

    AK_47();

    POS(63,5,Yellow);
    puts("AK-47");
    POS(109,35,LightCyan);
    puts("Attack + 80");
    POS(112,45,LightGreen);
    puts("-$200");

    POS(63,10,DarkGray);
    puts("M4A4");

    POS(60,15,DarkGray);
    puts("Desert Eagle");

    POS(63,20,DarkGray);
    puts("FAMAS");

    POS(64,25,DarkGray);
    puts("AWP");

    POS(63,45,LightGreen);
    printf("$%i", pVar->money);

    while (check==0) {

        com = getch();
        switch (com) {
            case 'w':   control_3--; break;
            case 's':   control_3++; break;
            case 'a':   check = 1;
                        clean_shop_left();
                        clean_shop_right();
                        continue;
                        break;
        }

        switch (control_3) {
            case 1:     POS(63,5,Yellow);
                        puts("AK-47");

                        POS(63,10,DarkGray);
                        puts("M4A4");

                        POS(60,15,DarkGray);
                        puts("Desert Eagle");

                        POS(63,20,DarkGray);
                        puts("FAMAS");

                        POS(64,25,DarkGray);
                        puts("AWP");

                        clean_shop_right();
                        POS(109,35,LightCyan);
                        puts("Attack + 80");
                        POS(112,45,LightGreen);
                        puts("-$200");
                        AK_47();
                    break;

            case 2:     POS(63,5,DarkGray);
                        puts("AK-47");

                        POS(63,10,Yellow);
                        puts("M4A4");

                        POS(60,15,DarkGray);
                        puts("Desert Eagle");

                        POS(63,20,DarkGray);
                        puts("FAMAS");

                        POS(64,25,DarkGray);
                        puts("AWP");

                        clean_shop_right();
                        POS(109,35,LightCyan);
                        puts("Attack + 60");
                        POS(112,45,LightGreen);
                        puts("-$150");
                        M4a4();
                    break;

            case 3:     POS(63,5,DarkGray);
                        puts("AK-47");

                        POS(63,10,DarkGray);
                        puts("M4A4");

                        POS(60,15,Yellow);
                        puts("Desert Eagle");

                        POS(63,20,DarkGray);
                        puts("FAMAS");

                        POS(64,25,DarkGray);
                        puts("AWP");

                        clean_shop_right();
                        POS(109,35,LightCyan);
                        puts("Attack + 30");
                        POS(112,45,LightGreen);
                        puts("-$50");
                        Desert_Eagle();
                    break;

            case 4:     POS(63,5,DarkGray);
                        puts("AK-47");

                        POS(63,10,DarkGray);
                        puts("M4A4");

                        POS(60,15,DarkGray);
                        puts("Desert Eagle");

                        POS(63,20,Yellow);
                        puts("FAMAS");

                        POS(64,25,DarkGray);
                        puts("AWP");

                        clean_shop_right();
                        POS(109,35,LightCyan);
                        puts("Attack + 50");
                        POS(112,45,LightGreen);
                        puts("-$100");
                        Famas();
                    break;

            case 5:     POS(63,5,DarkGray);
                        puts("AK-47");

                        POS(63,10,DarkGray);
                        puts("M4A4");

                        POS(60,15,DarkGray);
                        puts("Desert Eagle");

                        POS(63,20,DarkGray);
                        puts("FAMAS");

                        POS(64,25,Yellow);
                        puts("AWP");

                        clean_shop_right();
                        POS(109,35,LightCyan);
                        puts("Attack + 100");
                        POS(112,45,LightGreen);
                        puts("-$250");
                        Awp();
                    break;

            default:    if (control_3 > 5) {
                            POS(63,5,Yellow);
                            puts("AK-47");

                            POS(63,10,DarkGray);
                            puts("M4A4");

                            POS(60,15,DarkGray);
                            puts("Desert Eagle");

                            POS(63,20,DarkGray);
                            puts("FAMAS");

                            POS(64,25,DarkGray);
                            puts("AWP");

                            clean_shop_right();
                            POS(109,35,LightCyan);
                            puts("Attack + 100");
                            POS(112,45,LightGreen);
                            puts("-$200");
                            AK_47();
                            control_3 = 1;
                        }
                        else {
                            POS(63,5,DarkGray);
                            puts("AK-47");

                            POS(63,10,DarkGray);
                            puts("M4A4");

                            POS(60,15,DarkGray);
                            puts("Desert Eagle");

                            POS(63,20,DarkGray);
                            puts("FAMAS");

                            POS(64,25,Yellow);
                            puts("AWP");

                            clean_shop_right();
                            POS(109,35,LightCyan);
                            puts("Attack + 100");
                            POS(112,45,LightGreen);
                            puts("-$250");
                            Awp();
                            control_3 = 5;
                        }
                    break;
        }

        switch (com) {
            case 'd':   new_pVar = robot;
                        if (control_3==1) {
                            if (pVar->money >= 200) {
                                if(new_pVar->damage == 80) {
                                    POS(101,40,LightRed);
                                    puts("Вы уже приобрели это оружие");
                                }
                                else {
                                    strcpy(new_pVar->weapon, "AK-47");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 80;
                                    new_pVar->money = new_pVar->money - 200;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "AK-47");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 80;
                                    new_pVar->money = new_pVar->money - 200;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "AK-47");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 80;
                                    new_pVar->money = new_pVar->money - 200;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "AK-47");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 80;
                                    new_pVar->money = new_pVar->money - 200;

                                    POS(63,45,LightGreen);
                                    puts("             ");
                                    POS(63,45,LightGreen);
                                    printf("$%i", pVar->money);

                                    clean_result(robot, pVar);
                                    result(robot, pVar);
                                }
                            }
                            else {
                                POS(110,40,LightRed);
                                puts("Мало денег");
                            }
                        }
                        if (control_3==2) {
                            if (pVar->money >= 150) {
                                if(new_pVar->damage == 60) {
                                    POS(101,40,LightRed);
                                    puts("Вы уже приобрели это оружие");
                                }
                                else {
                                    strcpy(new_pVar->weapon, "M4A4");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 60;
                                    new_pVar->money = new_pVar->money - 150;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "M4A4");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 60;
                                    new_pVar->money = new_pVar->money - 150;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "M4A4");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 60;
                                    new_pVar->money = new_pVar->money - 150;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "M4A4");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 60;
                                    new_pVar->money = new_pVar->money - 150;


                                    POS(63,45,LightGreen);
                                    puts("             ");
                                    POS(63,45,LightGreen);
                                    printf("$%i", pVar->money);

                                    clean_result(robot, pVar);
                                    result(robot, pVar);
                                }
                            }
                            else {
                                POS(110,40,LightRed);
                                puts("Мало денег");
                            }
                        }
                        if (control_3==3) {
                            if (pVar->money >= 50) {
                                if(new_pVar->damage == 30) {
                                    POS(101,40,LightRed);
                                    puts("Вы уже приобрели это оружие");
                                }
                                else {
                                    strcpy(new_pVar->weapon, "Desert Eagle");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 30;
                                    new_pVar->money = new_pVar->money - 50;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "Desert Eagle");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 30;
                                    new_pVar->money = new_pVar->money - 50;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "Desert Eagle");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 30;
                                    new_pVar->money = new_pVar->money - 50;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "Desert Eagle");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 30;
                                    new_pVar->money = new_pVar->money - 50;


                                    POS(63,45,LightGreen);
                                    puts("             ");
                                    POS(63,45,LightGreen);
                                    printf("$%i", pVar->money);

                                    clean_result(robot, pVar);
                                    result(robot, pVar);
                                }
                            }
                            else {
                                POS(110,40,LightRed);
                                puts("Мало денег");
                            }
                        }
                        if (control_3==4) {
                            if (pVar->money >= 100) {
                                if(new_pVar->damage == 50) {
                                    POS(101,40,LightRed);
                                    puts("Вы уже приобрели это оружие");
                                }
                                else {
                                    strcpy(new_pVar->weapon, "FAMAS");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 50;
                                    new_pVar->money = new_pVar->money - 100;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "FAMAS");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 50;
                                    new_pVar->money = new_pVar->money - 100;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "FAMAS");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 50;
                                    new_pVar->money = new_pVar->money - 100;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "FAMAS");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 50;
                                    new_pVar->money = new_pVar->money - 100;

                                    POS(63,45,LightGreen);
                                    puts("             ");
                                    POS(63,45,LightGreen);
                                    printf("$%i", pVar->money);

                                    clean_result(robot, pVar);
                                    result(robot, pVar);
                                }
                            }
                            else {
                                POS(110,40,LightRed);
                                puts("Мало денег");
                            }
                        }
                        if (control_3==5) {
                            if (pVar->money >= 250) {
                                if(new_pVar->damage == 100) {
                                    POS(101,40,LightRed);
                                    puts("Вы уже приобрели это оружие");
                                }
                                else {
                                    strcpy(new_pVar->weapon, "AWP");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 100;
                                    new_pVar->money = new_pVar->money - 250;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "AWP");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 100;
                                    new_pVar->money = new_pVar->money - 250;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "AWP");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 100;
                                    new_pVar->money = new_pVar->money - 250;

                                    new_pVar++;
                                    strcpy(new_pVar->weapon, "AWP");
                                    if (new_pVar->damage!=0)
                                        new_pVar->damage = 0;
                                    new_pVar->damage += 100;
                                    new_pVar->money = new_pVar->money - 250;

                                    POS(63,45,LightGreen);
                                    puts("             ");
                                    POS(63,45,LightGreen);
                                    printf("$%i", pVar->money);

                                    clean_result(robot, pVar);
                                    result(robot, pVar);
                                }
                            }
                            else {
                                POS(110,40,LightRed);
                                puts("Мало денег");
                            }
                        }
                        break;
        }
    }

    return pVar;
}

struct Robot * Other(struct Robot robot[], struct Robot * pVar) {

    char com;
    int control_4 = 1;
    int check = 0;

    struct Robot * new_pVar = pVar;

    Kevlar_Vest();

    POS(60,5,Yellow);
    puts("Kevlar Vest");
    POS(107,35,LightCyan);
    puts("Protection + 100");
    POS(112,45,LightGreen);
    puts("-$100");

    POS(62,10,DarkGray);
    puts("Helmet");

    POS(63,45,LightGreen);
    printf("$%i", pVar->money);

    while (check==0) {

        com = getch();
        switch (com) {
            case 'w':   control_4--; break;
            case 's':   control_4++; break;
            case 'a':   check = 1;
                        clean_shop_left();
                        clean_shop_right();
                        continue;
                        break;
        }

        switch (control_4) {
            case 1:     POS(60,5,Yellow);
                        puts("Kevlar Vest");

                        POS(62,10,DarkGray);
                        puts("Helmet");

                        clean_shop_right();
                        POS(107,35,LightCyan);
                        puts("Protection + 100");
                        POS(112,45,LightGreen);
                        puts("-$100");
                        Kevlar_Vest();
                    break;

            case 2:     POS(60,5,DarkGray);
                        puts("Kevlar Vest");

                        POS(62,10,Yellow);
                        puts("Helmet");

                        clean_shop_right();
                        POS(107,35,LightCyan);
                        puts("Protection + 50");
                        POS(112,45,LightGreen);
                        puts("-$50");
                        Helmet();
                    break;

            default:    if (control_4 > 2) {
                            POS(60,5,Yellow);
                            puts("Kevlar Vest");

                            POS(62,10,DarkGray);
                            puts("Helmet");

                            clean_shop_right();
                            POS(107,35,LightCyan);
                            puts("Protection + 100");
                            POS(112,45,LightGreen);
                            puts("-$100");
                            Kevlar_Vest();
                            control_4 = 1;
                        }
                        else {
                            POS(60,5,DarkGray);
                            puts("Kevlar Vest");

                            POS(62,10,Yellow);
                            puts("Helmet");

                            clean_shop_right();
                            POS(107,35,LightCyan);
                            puts("Protection + 50");
                            POS(112,45,LightGreen);
                            puts("-$50");
                            Helmet();
                            control_4 = 2;
                        }
                    break;
        }

        switch (com) {
            case 'd':   new_pVar = robot;
                        if (control_4==1) {
                            if (pVar->money >= 100) {

                                if (new_pVar->defense==0 || new_pVar->defense==50) {
                                    new_pVar->defense += 100;
                                    new_pVar->money = new_pVar->money - 100;
                                }
                                else {
                                    POS(101,40,LightRed);
                                    puts("Вы уже приобрели эту защиту");
                                }

                                new_pVar++;
                                if (new_pVar->defense==0 || new_pVar->defense==50) {
                                    new_pVar->defense += 100;
                                    new_pVar->money = new_pVar->money - 100;
                                }

                                new_pVar++;
                                if (new_pVar->defense==0 || new_pVar->defense==50) {
                                    new_pVar->defense += 100;
                                    new_pVar->money = new_pVar->money - 100;
                                }

                                new_pVar++;
                                if (new_pVar->defense==0 || new_pVar->defense==50) {
                                    new_pVar->defense += 100;
                                    new_pVar->money = new_pVar->money - 100;
                                }

                                POS(63,45,LightGreen);
                                puts("             ");
                                POS(63,45,LightGreen);
                                printf("$%i", pVar->money);

                                clean_result(robot, pVar);
                                result(robot, pVar);
                            }
                            else {
                                POS(110,40,LightRed);
                                puts("Мало денег");
                            }
                        }
                        if (control_4==2) {
                            if (pVar->money >= 50) {

                                if (new_pVar->defense==0 || new_pVar->defense==100) {
                                    new_pVar->defense += 50;
                                    new_pVar->money = new_pVar->money - 50;
                                }
                                else {
                                    POS(101,40,LightRed);
                                    puts("Вы уже приобрели эту защиту");
                                }

                                new_pVar++;
                                if (new_pVar->defense==0 || new_pVar->defense==100) {
                                    new_pVar->defense += 50;
                                    new_pVar->money = new_pVar->money - 50;
                                }

                                new_pVar++;
                                if (new_pVar->defense==0 || new_pVar->defense==100) {
                                    new_pVar->defense += 50;
                                    new_pVar->money = new_pVar->money - 50;
                                }

                                new_pVar++;
                                if (new_pVar->defense==0 || new_pVar->defense==100) {
                                    new_pVar->defense += 50;
                                    new_pVar->money = new_pVar->money - 50;
                                }

                                POS(63,45,LightGreen);
                                puts("             ");
                                POS(63,45,LightGreen);
                                printf("$%i", pVar->money);

                                clean_result(robot, pVar);
                                result(robot, pVar);
                            }
                            else {
                                POS(110,40,LightRed);
                                puts("Мало денег");
                            }
                        }
                        break;
        }
    }

    return pVar;
}


void diagram (int x, int y) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i,j;

    for (i=x; i<=x+4; i++)
        for (j=45; j>=45-y; j--) {
            POS(i,j,Black);
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
            puts(" ");
        }
    SetConsoleTextAttribute(hConsole, LightGray);
}

void info(struct Robot robot[], struct Robot * pVar) {

    POS(85,4,LightMagenta);
    printf("Health");
    POS(86,8,LightGreen);
    printf("%i", pVar->health);

    POS(100,4,LightCyan);
    printf("Protection");
    POS(103,8,LightGreen);
    printf("%i", pVar->protection);

    POS(120,4,LightCyan);
    printf("Attack");
    POS(121,8,LightGreen);
    printf("%i", pVar->attack);

    POS(135,4,LightRed);
    printf("Weapon");
    POS(135,8,LightGreen);
    printf("%s", pVar->weapon);

    if (pVar->health == 400)        diagram (86,25);
    if (pVar->protection == 200)    diagram (103,30);
    if (pVar->attack == 100)        diagram (120,30);

    if (pVar->health == 350)        diagram (86,20);
    if (pVar->protection == 200)    diagram (103,30);
    if (pVar->attack == 150)        diagram (120,35);

    if (pVar->health == 700)        diagram (86,35);
    if (pVar->protection == 250)    diagram (103,35);
    if (pVar->attack == 50)         diagram (120,20);

    if (pVar->health == 500)        diagram (86,30);
    if (pVar->protection == 200)    diagram (103,30);
    if (pVar->attack == 75)         diagram (120,25);


    if (strncmp(pVar->weapon, "AK-47", 5)==0)          diagram (136,30);
    if (strncmp(pVar->weapon, "M4A4", 4)==0)           diagram (135,25);
    if (strncmp(pVar->weapon, "Desert Eagle", 12)==0)  diagram (135,15);
    if (strncmp(pVar->weapon, "FAMAS", 5)==0)          diagram (135,20);
    if (strncmp(pVar->weapon, "AWP", 3)==0)            diagram (135,35);
}

void Kuratas(struct Robot robot[], struct Robot * pVar) {
    pVar+=0;
    info(robot, pVar);
}

void Scorpio(struct Robot robot[], struct Robot * pVar) {
    pVar+=1;
    info(robot, pVar);
}

void Terminator(struct Robot robot[], struct Robot * pVar) {
    pVar+=2;
    info(robot, pVar);
}

void Maxopo(struct Robot robot[], struct Robot * pVar) {
    pVar+=3;
    info(robot, pVar);
}

struct Robot * unit(struct Robot robot[], struct Robot * pVar) {

    char com;
    int control_5 = 1;
    int check = 0;

    struct Robot * new_pVar = robot;

    POS(63,5,Yellow);
    puts("Kuratas");

    POS(63,10,DarkGray);
    puts("Scorpio");

    POS(61,15,DarkGray);
    puts("Terminator");

    POS(63,20,DarkGray);
    puts("Махоро");

    Kuratas(robot, new_pVar);

    while (check==0) {

        com = getch();
        switch (com) {
            case 'w':   control_5--; break;
            case 's':   control_5++; break;
            case 'a':   check = 1;
                        clean();
                        continue;
                        break;
        }

        switch (control_5) {
            case 1:     POS(63,5,Yellow);
                        puts("Kuratas");

                        POS(63,10,DarkGray);
                        puts("Scorpio");

                        POS(61,15,DarkGray);
                        puts("Terminator");

                        POS(63,20,DarkGray);
                        puts("Махоро");

                        clean_shop_right();
                        Kuratas(robot, new_pVar);
                    break;

            case 2:     POS(63,5,DarkGray);
                        puts("Kuratas");

                        POS(63,10,Yellow);
                        puts("Scorpio");

                        POS(61,15,DarkGray);
                        puts("Terminator");

                        POS(63,20,DarkGray);
                        puts("Махоро");

                        clean_shop_right();
                        Scorpio(robot, new_pVar);
                    break;

            case 3:     POS(63,5,DarkGray);
                        puts("Kuratas");

                        POS(63,10,DarkGray);
                        puts("Scorpio");

                        POS(61,15,Yellow);
                        puts("Terminator");

                        POS(63,20,DarkGray);
                        puts("Махоро");

                        clean_shop_right();
                        Terminator(robot, new_pVar);
                    break;

            case 4:     POS(63,5,DarkGray);
                        puts("Kuratas");

                        POS(63,10,DarkGray);
                        puts("Scorpio");

                        POS(61,15,DarkGray);
                        puts("Terminator");

                        POS(63,20,Yellow);
                        puts("Махоро");

                        clean_shop_right();
                        Maxopo(robot, new_pVar);
                    break;

            default:    if (control_5 > 4) {
                            POS(63,5,Yellow);
                            puts("Kuratas");

                            POS(63,10,DarkGray);
                            puts("Scorpio");

                            POS(61,15,DarkGray);
                            puts("Terminator");

                            POS(63,20,DarkGray);
                            puts("Махоро");

                            clean_shop_right();
                            Kuratas(robot, new_pVar);
                            control_5 = 1;
                        }
                        else {
                            POS(63,5,DarkGray);
                            puts("Kuratas");

                            POS(63,10,DarkGray);
                            puts("Scorpio");

                            POS(61,15,DarkGray);
                            puts("Terminator");

                            POS(63,20,Yellow);
                            puts("Махоро");

                            clean_shop_right();
                            Maxopo(robot, new_pVar);
                            control_5 = 4;
                        }
                    break;
        }

        switch (com) {
            case 'd':   if (control_5==1) {
                            pVar = new_pVar;
                            clean_result();
                            result(robot, pVar);
                        }
                        if (control_5==2) {
                            new_pVar+=1;
                            pVar = new_pVar;
                            clean_result();
                            result(robot, pVar);
                            new_pVar-=1;
                        }
                        if (control_5==3) {
                            new_pVar+=2;
                            pVar = new_pVar;
                            clean_result();
                            result(robot, pVar);
                            new_pVar-=2;
                        }
                        if (control_5==4) {
                            new_pVar+=3;
                            pVar = new_pVar;
                            clean_result();
                            result(robot, pVar);
                            new_pVar-=3;
                        }
                        break;
        }
    }

    return pVar;
}

struct Robot * battle(struct Robot robot[], struct Robot * pVar, struct Robot * battle_pVar) {

    srand(time(NULL));
    int r = rand()%4;

    battle_pVar = robot;

    POS(30,5,LightGray);
    printf("Name:       %s", pVar->name);
    POS(30,6,LightGray);
    printf("Weapon:     %s", pVar->weapon);
    POS(30,8,LightGray);
    printf("Health:       %i", pVar->health);
    POS(30,9,LightGray);
    printf("Protection:   %i", pVar->protection);
    POS(30,10,LightGray);
    printf("Attack:       %i", pVar->attack);
    POS(30,11,LightGray);
    printf("Damage:       %i", pVar->damage);
    POS(30,12,LightGray);
    printf("Defense:      %i", pVar->defense);

    battle_pVar+=r;

    POS(101,5,LightGray);
    printf("Name:       %s", battle_pVar->name);
    POS(101,6,LightGray);
    printf("Weapon:     %s", battle_pVar->weapon);
    POS(101,8,LightGray);
    printf("Health:       %i", battle_pVar->health);
    POS(101,9,LightGray);
    printf("Protection:   %i", battle_pVar->protection);
    POS(101,10,LightGray);
    printf("Attack:       %i", battle_pVar->attack);
    POS(101,11,LightGray);
    printf("Damage:       %i", battle_pVar->damage);
    POS(101,12,LightGray);
    printf("Defense:      %i", battle_pVar->defense);

    return battle_pVar;
}

int vs(struct Robot * pVar, struct Robot * battle_pVar) {
    int victory;

    int health_first = pVar->health;
    int health_second = battle_pVar->health;

    int protection_first = pVar->protection;
    int protection_second = battle_pVar->protection;

    int attack_first = pVar->attack;
    int attack_second = battle_pVar->attack;

    int damage_first = pVar->damage;
    int damage_second = battle_pVar->damage;

    int defense_first = pVar->defense;
    int defense_second = battle_pVar->defense;

    int sum_first;
    int sum_second;

    while (health_first > 0 && health_second > 0) {
        sum_second = (protection_second + defense_second) - (attack_first + damage_first);
        if (sum_second < 0) {
            health_second+=sum_second;
        }
        else
            attack_first+=50;

        sum_first = (protection_first + defense_first) - (attack_second + damage_second);
        if (sum_first < 0) {
            health_first+=sum_first;
        }
        else
            attack_second+=50;
    }

    if (health_first >= health_second)
        victory = 1;
    else
        victory = 0;

    return victory;
}

void save(struct Robot robot[], struct Robot * pVar, struct Robot * battle_pVar) {

    FILE * file = fopen("file.txt", "w+");

    if (file == NULL) {
        POS(118,47,LightGray);
        puts("Не найден нужный файл...");
    }
    else {
        POS(116,47,LightGray);
        puts("Cохранение прошло успешно...");

        fprintf(file, "A new round:\n\n");
        fprintf(file, "Name:       %s\nWeapon:     %s\nHealth:       %i\nProtection: %i + %i\nAttack:     %i + %i\n", pVar->name, pVar->weapon, pVar->health, pVar->protection, pVar->defense, pVar->attack, pVar->damage);
        fprintf(file, "\n        vs\n\n");
        fprintf(file, "Name:       %s\nWeapon:     %s\nHealth:       %i\nProtection: %i + %i\nAttack:     %i + %i\n", battle_pVar->name, battle_pVar->weapon, battle_pVar->health, battle_pVar->protection, battle_pVar->defense, battle_pVar->attack, battle_pVar->damage);
    }

    fclose(file);
}

void download(struct Robot robot[], struct Robot * pVar, struct Robot * battle_pVar) {

    char str[25];
    int i;
    FILE * file = fopen("file.txt", "r+");

    if (fscanf (file, "%s", str) == EOF) {
        POS(118,47,LightGray);
        puts("Сохранений не обнаружено");
    }
    else
    if (file == NULL) {
        POS(118,47,LightGray);
        puts("Не найден нужный файл...");
    }
    else {
        POS(117,47,LightGray);
        puts("Загрузка прошла успешно...");

        for(i=0; i<15; i++) {
            fgets(str, 25, file);

            if (i>1 && i<7) {
                POS(50,2+i,LightGreen);
                printf("%s", str);
            }
            if (i==8) {
                POS(50,3+i,Yellow);
                printf("%s", str);
            }
            if (i>9 && i<15) {
                POS(50,4+i,LightRed);
                printf("%s", str);
            }
        }
        int victory = vs(pVar, battle_pVar);

        if (victory == 1) {
            POS(80,11,Green);
            puts("Вы победили");
        }
        else {
            POS(80,11,Red);
            puts("Вы проиграли");
        }
    }

    fclose(file);

    POS(63,45,LightGray);
    printf("Нажмите для продолжения...");
    getch();
    clean();
}

int main() {

    setlocale(LC_ALL,"rus");

    char com;
    int control_1 = 1;
    int check = 0;

    struct Robot * pVar = malloc(sizeof(struct Robot));
    struct Robot * new_pVar = malloc(sizeof(struct Robot));
    struct Robot * battle_pVar = malloc(sizeof(struct Robot));

    struct Robot robot[4] =  {  {"Kuratas", "Nothing", 400, 200, 100, 0, 0, 1000},
                                {"Scorpio", "Nothing", 350, 200, 150, 0, 0, 1000},
                                {"Terminator", "Nothing", 700, 250, 50, 0, 0, 1000},
                                {"Махоро", "Nothing", 500, 200, 75, 0, 0, 1000},
                           };

    pVar = robot;
    new_pVar = robot;
    battle_pVar = robot;

    POS(19,3,Yellow);
    puts("Играть");

    POS(18,6,DarkGray);
    puts("Загрузить");

    POS(19,9,DarkGray);
    puts("Магазин");

    POS(20,12,DarkGray);
    puts("Юниты");

    POS(20,15,DarkGray);
    puts("Выйти");

    while (check==0) {

        com = getch();
        switch (com) {
            case 'w': control_1--; break;
            case 's': control_1++; break;
        }

        switch (control_1) {
            case 1:     POS(19,3,Yellow);
                        puts("Играть");

                        POS(18,6,DarkGray);
                        puts("Загрузить");

                        POS(19,9,DarkGray);
                        puts("Магазин");

                        POS(20,12,DarkGray);
                        puts("Юниты");

                        POS(20,15,DarkGray);
                        puts("Выйти");
                    break;

            case 2:     POS(19,3,DarkGray);
                        puts("Играть");

                        POS(18,6,Yellow);
                        puts("Загрузить");

                        POS(19,9,DarkGray);
                        puts("Магазин");

                        POS(20,12,DarkGray);
                        puts("Юниты");

                        POS(20,15,DarkGray);
                        puts("Выйти");
                    break;

            case 3:     POS(19,3,DarkGray);
                        puts("Играть");

                        POS(18,6,DarkGray);
                        puts("Загрузить");

                        POS(19,9,Yellow);
                        puts("Магазин");

                        POS(20,12,DarkGray);
                        puts("Юниты");

                        POS(20,15,DarkGray);
                        puts("Выйти");
                    break;

            case 4:     POS(19,3,DarkGray);
                        puts("Играть");

                        POS(18,6,DarkGray);
                        puts("Загрузить");

                        POS(19,9,DarkGray);
                        puts("Магазин");

                        POS(20,12,Yellow);
                        puts("Юниты");

                        POS(20,15,DarkGray);
                        puts("Выйти");
                    break;

            case 5:     POS(19,3,DarkGray);
                        puts("Играть");

                        POS(18,6,DarkGray);
                        puts("Загрузить");

                        POS(19,9,DarkGray);
                        puts("Магазин");

                        POS(20,12,DarkGray);
                        puts("Юниты");

                        POS(20,15,Yellow);
                        puts("Выйти");
                    break;

            default:    if (control_1 > 5) {
                            POS(19,3,Yellow);
                            puts("Играть");

                            POS(18,6,DarkGray);
                            puts("Загрузить");

                            POS(19,9,DarkGray);
                            puts("Магазин");

                            POS(20,12,DarkGray);
                            puts("Юниты");

                            POS(20,15,DarkGray);
                            puts("Выйти");
                            control_1 = 1;
                        }
                        else {
                            POS(19,3,DarkGray);
                            puts("Играть");

                            POS(18,6,DarkGray);
                            puts("Загрузить");

                            POS(19,9,DarkGray);
                            puts("Магазин");

                            POS(20,12,DarkGray);
                            puts("Юниты");

                            POS(20,15,Yellow);
                            puts("Выйти");
                            control_1 = 5;
                        }
                    break;
        }

        if (com=='d' && control_1==1) {
            system("cls");
            battle_pVar = battle(robot, pVar, battle_pVar);
            loading();
            save(robot, pVar, battle_pVar);

            if (vs(pVar, battle_pVar) == 1) {
                pVar->money = pVar->money + 300;
                POS(70,8,Green);
                puts("Вы победили");
            }
            else {
                POS(68,8,Red);
                puts("Вы проиграли");

                new_pVar = robot;
                strcpy(new_pVar->weapon, "Nothing");
                new_pVar->damage = 0;

                new_pVar++;
                strcpy(new_pVar->weapon, "Nothing");
                new_pVar->damage = 0;

                new_pVar++;
                strcpy(new_pVar->weapon, "Nothing");
                new_pVar->damage = 0;

                new_pVar++;
                strcpy(new_pVar->weapon, "Nothing");
                new_pVar->damage = 0;
            }
            new_pVar = robot;
            new_pVar->defense = 0;

            new_pVar++;
            new_pVar->defense = 0;

            new_pVar++;
            new_pVar->defense = 0;

            new_pVar++;
            new_pVar->defense = 0;

            POS(63,45,LightGray);
            printf("Нажмите для продолжения...");
            getch();

            system("cls");

            POS(19,3,Yellow);
            puts("Играть");

            POS(18,6,DarkGray);
            puts("Загрузить");

            POS(19,9,DarkGray);
            puts("Магазин");

            POS(20,12,DarkGray);
            puts("Юниты");

            POS(20,15,DarkGray);
            puts("Выйти");

            result(robot, pVar);
        }
        if (com=='d' && control_1==2) {
            loading();
            download(robot, pVar, battle_pVar);
        }
        if (com=='d' && control_1==3) {
            window();
            pVar = shop(robot, pVar);
        }
        if (com=='d' && control_1==4) {
            window();
            pVar = unit(robot, pVar);
        }
        if (com=='d' && control_1==5) {
            system("cls");
            check = 1;
        }
    }
    free(pVar);
    free(new_pVar);
    free(battle_pVar);

    POS(0,0,LightGray);
    return 0;
}
