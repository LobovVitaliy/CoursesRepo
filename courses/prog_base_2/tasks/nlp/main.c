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

    // определяем размер файла
    fseek(nlp , 0 , SEEK_END);  // устанавливаем позицию в конец файла
    long lSize = ftell(nlp);    // получаем размер в байтах
    rewind(nlp);                // устанавливаем указатель в конец файла

    char * buffer = (char*) malloc(sizeof(char) * lSize); // выделить память для хранения содержимого файла
    size_t result = fread(buffer, 1, lSize, nlp);  // считываем файл в буфер

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
