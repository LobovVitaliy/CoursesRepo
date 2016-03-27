#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

#include <windows.h>

typedef HANDLE Writer_t;
typedef struct symbol_s symbol_t;

Writer_t * Writer_new(HANDLE hMutex, char * symbol, char * string);
void Writer_free(Writer_t * self);
DWORD writerFunc(LPVOID args);

#endif
