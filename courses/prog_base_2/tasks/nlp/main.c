#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nlp.h"

int main()
{
    FILE * nlp = fopen("nlp.txt", "rb");

    if (nlp == NULL)
    {
        fputs("Error", stderr);
        exit(1);
    }

    // ���������� ������ �����
    fseek(nlp , 0 , SEEK_END);  // ������������� ������� � ����� �����
    long lSize = ftell(nlp);    // �������� ������ � ������
    rewind(nlp);                // ������������� ��������� � ����� �����

    char * buffer = (char*) malloc(sizeof(char) * lSize); // �������� ������ ��� �������� ����������� �����
    size_t result = fread(buffer, 1, lSize, nlp);  // ��������� ���� � �����

    if (result != lSize)
    {
        fputs("Error", stderr);
        exit(3);
    }

    text_t * text = text_new();

    text_divide(text, buffer);
    text_write(text, "output.txt");

    text_free(text);
    return 0;
}
