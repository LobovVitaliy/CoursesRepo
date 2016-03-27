#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <string.h>

#include "Writer.h"

struct str {
    char * string;
} s;

HANDLE hMutexW;

Writer_t * Writer_new(HANDLE hMutex, char * symbol, char * string) {
    s.string = string;
    LPVOID ctx = symbol;
    hMutexW = hMutex;

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

    char * symbol = (char *) args;
    int size = strlen(s.string);
    int i = 0;

    for(i = size - 1; i >= 0; i--) {
        WaitForSingleObject(hMutexW, INFINITE);
            symbol = s.string[i];
            Sleep(100);
        ReleaseMutex(hMutexW);
    }
}
