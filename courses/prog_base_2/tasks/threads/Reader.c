#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <string.h>

#include "Reader.h"

HANDLE hMutexR;

Reader_t * Reader_new(HANDLE hMutex, char * symbol) {
    LPVOID ctx = symbol;
    hMutexR = hMutex;

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

    char * symbol = (char *) args;
    char str[] = {"!%^&*()–+={}|~[]\;':<>?,./#"};
    int i = 0;

    while (1) {

        WaitForSingleObject(hMutexR, INFINITE);

        for(i = 0; i < strlen(str); i++) {
            if(symbol == str[i]) {
                printf("%c ", symbol);
                break;
            }
        }

        ReleaseMutex(hMutexR);
    }
}
