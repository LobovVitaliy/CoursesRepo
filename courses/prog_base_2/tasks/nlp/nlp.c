#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nlp.h"

typedef struct word_s {
    char word[50];
} word_t;

word_t * word_new()
{
    return malloc(sizeof(struct word_s));
}

typedef struct sentence_s {
    char sentence[10000];
    word_t * word[1000];
    int countWord;
} sentence_t;

sentence_t * sentence_new()
{
    sentence_t * self = malloc(sizeof(struct sentence_s));
    self->countWord = 0;
    return self;
}

struct text_s {
    sentence_t * sentence[100000];
    int countSentence;
};

text_t * text_new()
{
    text_t * self = malloc(sizeof(struct text_s));
    self->countSentence = 0;
    return self;
}

void text_free(text_t * self)
{
    for(int i = 0; i < self->countSentence; i++)
    {
        for(int j = 0; j < self->sentence[i]->countWord; j++)
        {
            free(self->sentence[i]->word[j]);
        }
        free(self->sentence[i]);
    }
    free(self);
}


void text_divide(text_t * self, char * text)
{
    char a;
    int i = 0;
    int iWord = 0;
    int iSentence = 0;

    while (i != strlen(text))
    {
        self->sentence[self->countSentence] = sentence_new();

        do
        {
            a = text[i];
            if(a != '\n') self->sentence[self->countSentence]->sentence[iSentence++] = a;
            i++;
        }
        while (a != '.' && a != '!' && a != '?');

        self->sentence[self->countSentence]->sentence[iSentence] = '\0';
        if(text[i] == ' ') i++;
        self->countSentence++;
        iSentence = 0;
    }

    /*for(int k = 0; k < self->countSentence; k++)
    {
        puts(self->sentence[k]->sentence);
    }*/

    for(int k = 0, i = 0; k < self->countSentence; k++, i = 0)
    {
        self->sentence[k]->word[self->sentence[k]->countWord] = word_new();

        do
        {
            a = self->sentence[k]->sentence[i];

            if(a == ',')
            {
                i++;
                a = self->sentence[k]->sentence[i];
            }

            if(a == ' ' || a == '.' || a == '!' || a == '?' || a == '/')
            {
                self->sentence[k]->word[self->sentence[k]->countWord]->word[iWord] = '\0';
                //puts(self->sentence[k]->word[self->sentence[k]->countWord]->word);
                self->sentence[k]->countWord++;
                self->sentence[k]->word[self->sentence[k]->countWord] = word_new();
                iWord = 0;
            }
            else
            {
                self->sentence[k]->word[self->sentence[k]->countWord]->word[iWord++] = a;
            }

            i++;
        }
        while (a != '.' && a != '!' && a != '?');
        //puts("");
    }
}

void text_write(text_t * self, char * nameFile)
{
    FILE * output = fopen(nameFile, "w");
    if (output == NULL) return;

    int check = 0;
    int checkNewLine = 0;

    for(int i = 0; i < self->countSentence; i++)
    {
        checkNewLine = 0;
        for(int j = 0; j < self->sentence[i]->countWord; j++)
        {
            check = 0;
            char * str = self->sentence[i]->word[j]->word;

            if(strncmp(str, "in", 2) == 0) check = 1;
            else if(strncmp(str, "un", 2) == 0) check = 1;
            else if(strncmp(str, "non", 3) == 0) check = 1;

            if(check == 1)
            {
                checkNewLine = 1;
                fwrite(str, strlen(str), 1, output);
                fwrite(", ", strlen(", "), 1, output);
            }
        }
        if(checkNewLine == 1) fwrite("\n", strlen("\n"), 1, output);
    }

    fclose(output);
}
