#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale.h>

// вариант 12

struct Student {

    char nameS[25];
    int a;
    struct Work * p;
};

struct Work {

    char nameW[25];
};

//вывод уже определенной структуры
void pf() {

    struct Student std[3] =  {  {"Василий", 4, "Курсовая работа: Структуры"},
                                {"Кирил", 3, "Курсовая работа: Файлы"},
                                {"Влад", 5, "Курсовая работа: Указатели"}
                            } ;
    struct Student * pVarS = std;
    int i;

    for (i=0; i<3; i++) {
        printf("Имя студента: %s\n", pVarS->nameS);
        printf("Бал студента: %i\n", pVarS->a);
        printf("Название курсовой работи: %s\n", pVarS->p->nameW);
        puts("");
        pVarS++;
    }
}

//вывод того что вводишь сам
void prf(struct Student st[3], struct Work kurs[3], struct Student * pVar, struct Work * pVarK) {

    int i;

    pVar = st;
    pVarK = kurs;

    for (i=0; i<3; i++) {
        printf("\nИмя студента: %s\nБал студента: %i", pVar->nameS, pVar->a);
        printf("\nНазвание курсовой работи: %s", pVarK->nameW);
        puts("");
        pVar++;
        pVarK++;
    }
}

//сам вводишь
void print(struct Student st[3], struct Work kurs[3], struct Student * pVar, struct Work * pVarK) {

    char name[25];
    int i;

    for (i=0; i<3; i++) {
        printf("\nВведите имя студента: ");
        gets(name);
        strcpy(pVar->nameS, name);
        printf("Введите бал студента за семестр: ");
        scanf("%i", &(pVar->a));

        printf("Введите название курсовой работи: ");
        fflush(stdin);
        gets(name);
        strcpy(pVarK->nameW, name);

        pVar++;
        pVarK++;
    }
}

//инфо про студентов у которых больше 50 баллов
void info(struct Student st[3], struct Work kurs[3], struct Student * pVar, struct Work * pVarK) {

    int i;

    for (i=0; i<3; i++) {
        if (((pVar)->a) > 50) {
            printf("\nИмя студента: %s\nБал студента: %i", pVar->nameS, pVar->a);
            printf("\nНазвание курсовой работи: %s", pVarK->nameW);
            puts("");
        }
        pVar++;
        pVarK++;
    }
}

int main()
{
    setlocale(LC_ALL,"rus");

    struct Student st[3];
    struct Work kurs[3];

    struct Student * pVar = st;
    struct Work * pVarK = kurs;

    char name[25];
    char qw[25];

    puts("Вывел информацию про структуры со значением по умолчанию:\n");
    pf();
    puts("\nЗаполнить значения:\n");
    print(st, kurs, pVar, pVarK);
    puts("\nСозданые обьекты:");
    prf(st, kurs, pVar, pVarK);
    puts("\nИнформация про все курсовые работы, у студентов, которые имеют больше чем 50 баллов:");
    info(st, kurs, pVar, pVarK);

    return 0;
}
