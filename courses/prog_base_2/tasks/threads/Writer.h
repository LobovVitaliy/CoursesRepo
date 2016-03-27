#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

struct symbol_s {
    char symbol;
    HANDLE mutex;
    char * string;
};

typedef struct symbol_s symbol_t;

typedef HANDLE Writer_t;

Writer_t * Writer_new(symbol_t * symbol);
void Writer_free(Writer_t * self);
DWORD writerFunc(LPVOID args);

#endif
