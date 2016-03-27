#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include "Writer.h"

typedef HANDLE Reader_t;

Reader_t * Reader_new(symbol_t * symbol);
void Reader_free(Reader_t * self);
DWORD readerFunc(LPVOID args);

#endif
