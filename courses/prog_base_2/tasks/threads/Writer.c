#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <string.h>

#include "Writer.h"

Writer_t * Writer_new(symbol_t * symbol) {

    LPVOID ctx = symbol;

    return CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) writerFunc,
        (LPVOID)ctx,
        0,
        NULL);
}

void Writer_free(Writer_t * self) {
    CloseHandle(self);
}

DWORD writerFunc(LPVOID args) {

    symbol_t * point = (symbol_t *) args;

    int size = strlen(point->string);
    int i = 0;

    for(i = size - 1; i >= 0; i--) {
        WaitForSingleObject(point->mutex, INFINITE);
            point->symbol = point->string[i];
            Sleep(100);
        ReleaseMutex(point->mutex);
    }
}
