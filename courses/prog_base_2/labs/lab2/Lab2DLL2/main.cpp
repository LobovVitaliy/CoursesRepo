#include "main.h"

int compare(queue_s * self) {
    int sum = 0;
    for (int i = 0; i < queue_getCount(self); i++) {
        sum += queue_getElement(self, i);
    }
    if (sum > 100)
        return 1;
    else
        return 0;
}

void reaction(queue_s * self) {
    int sum = 101;
    while (sum >= 50) {
        int delElement = queue_delete(self);
        sum = 0;
        for (int i = 0; i < queue_getCount(self); i++) {
           sum += queue_getElement(self, i);
        }
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
