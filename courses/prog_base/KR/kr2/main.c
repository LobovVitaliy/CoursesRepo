#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale.h>

// ������� 12

struct Student {

    char nameS[25];
    int a;
    struct Work * p;
};

struct Work {

    char nameW[25];
};

//����� ��� ������������ ���������
void pf() {

    struct Student std[3] =  {  {"�������", 4, "�������� ������: ���������"},
                                {"�����", 3, "�������� ������: �����"},
                                {"����", 5, "�������� ������: ���������"}
                            } ;
    struct Student * pVarS = std;
    int i;

    for (i=0; i<3; i++) {
        printf("��� ��������: %s\n", pVarS->nameS);
        printf("��� ��������: %i\n", pVarS->a);
        printf("�������� �������� ������: %s\n", pVarS->p->nameW);
        puts("");
        pVarS++;
    }
}

//����� ���� ��� ������� ���
void prf(struct Student st[3], struct Work kurs[3], struct Student * pVar, struct Work * pVarK) {

    int i;

    pVar = st;
    pVarK = kurs;

    for (i=0; i<3; i++) {
        printf("\n��� ��������: %s\n��� ��������: %i", pVar->nameS, pVar->a);
        printf("\n�������� �������� ������: %s", pVarK->nameW);
        puts("");
        pVar++;
        pVarK++;
    }
}

//��� �������
void print(struct Student st[3], struct Work kurs[3], struct Student * pVar, struct Work * pVarK) {

    char name[25];
    int i;

    for (i=0; i<3; i++) {
        printf("\n������� ��� ��������: ");
        gets(name);
        strcpy(pVar->nameS, name);
        printf("������� ��� �������� �� �������: ");
        scanf("%i", &(pVar->a));

        printf("������� �������� �������� ������: ");
        fflush(stdin);
        gets(name);
        strcpy(pVarK->nameW, name);

        pVar++;
        pVarK++;
    }
}

//���� ��� ��������� � ������� ������ 50 ������
void info(struct Student st[3], struct Work kurs[3], struct Student * pVar, struct Work * pVarK) {

    int i;

    for (i=0; i<3; i++) {
        if (((pVar)->a) > 50) {
            printf("\n��� ��������: %s\n��� ��������: %i", pVar->nameS, pVar->a);
            printf("\n�������� �������� ������: %s", pVarK->nameW);
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

    puts("����� ���������� ��� ��������� �� ��������� �� ���������:\n");
    pf();
    puts("\n��������� ��������:\n");
    print(st, kurs, pVar, pVarK);
    puts("\n�������� �������:");
    prf(st, kurs, pVar, pVarK);
    puts("\n���������� ��� ��� �������� ������, � ���������, ������� ����� ������ ��� 50 ������:");
    info(st, kurs, pVar, pVarK);

    return 0;
}
