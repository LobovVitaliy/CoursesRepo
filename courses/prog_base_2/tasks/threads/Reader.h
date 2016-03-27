#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include <windows.h>

typedef HANDLE Reader_t;
typedef struct symbol_s symbol_t;

Reader_t * Reader_new(HANDLE hMutex, char * symbol);
void Reader_free(Reader_t * self);
DWORD readerFunc(LPVOID args);

#endif
