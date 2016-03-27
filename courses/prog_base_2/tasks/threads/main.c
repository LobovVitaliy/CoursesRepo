#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <string.h>

#include "Writer.h"
#include "Reader.h"

int main(void) {

    symbol_t data;

    data.symbol = 'a';
    data.mutex = CreateMutex(NULL, FALSE, NULL);
    data.string = "Lobov,Vitaliy;Writes.Programme!";

    symbol_t * symbol = &data;

    Writer_t * w1 = Writer_new(symbol);
    Writer_t * w2 = Writer_new(symbol);

    Reader_t * r1 = Reader_new(symbol);
    Reader_t * r2 = Reader_new(symbol);
    Reader_t * r3 = Reader_new(symbol);

    WaitForSingleObject(w1, INFINITE);
    ReleaseMutex(w1);

    Writer_free(w1);
    Writer_free(w2);

    Reader_free(r1);
    Reader_free(r2);
    Reader_free(r3);

    CloseHandle(data.mutex);

    return 0;
}
