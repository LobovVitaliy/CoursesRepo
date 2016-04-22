#include "main.h"

int compare(queue_t * self) {
    if (queue_getCount(self) > 10)
        return 1;
    else
        return 0;
}

void reaction(queue_t * self) {
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += queue_delete(self);
    }
    printf("Sum = %i\n", sum);
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
