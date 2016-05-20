#ifndef NLP_H_INCLUDED
#define NLP_H_INCLUDED

typedef struct text_s text_t;

text_t * text_new();
void text_free(text_t * self);

void text_divide(text_t * self, char * text);
void text_write(text_t * self, char * nameFile);

#endif // NLP_H_INCLUDED

