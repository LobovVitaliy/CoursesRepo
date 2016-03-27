#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <string.h>

#include "Writer.h"
#include "Reader.h"

struct symbol_s {
    char symbol;
} x;

typedef struct symbol_s symbol_t;

HANDLE hMutex;

int main(void) {

    x.symbol = 'a';
    symbol_t * symbol = &x;

    hMutex = CreateMutex(NULL, FALSE, NULL);

    Writer_t * w = Writer_new(hMutex, symbol->symbol, "Lobov,Vitaliy;Writes.Programme!");
    Reader_t * r = Reader_new(hMutex, symbol->symbol);

    WaitForSingleObject(w, INFINITE);

    Writer_free(w);
    Reader_free(r);

    CloseHandle(hMutex);

    return 0;
}
