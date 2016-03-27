#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <string.h>

#include "Reader.h"

Reader_t * Reader_new(symbol_t * symbol) {

    LPVOID ctx = symbol;

    return CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) readerFunc,
        (LPVOID)ctx,
        0,
        NULL);
}

void Reader_free(Reader_t * self) {
    CloseHandle(self);
}

DWORD readerFunc(LPVOID args) {

    symbol_t * point = (symbol_t *) args;
    char str[] = {"!%^&*()–+={}|~[]\;':<>?,./#"};
    int i = 0;

    while (1) {

        WaitForSingleObject(point->mutex, INFINITE);

        for(i = 0; i < strlen(str); i++) {
            if(point->symbol == str[i]) {
                printf("%c ", point->symbol);
                break;
            }
        }

        ReleaseMutex(point->mutex);
    }
}
