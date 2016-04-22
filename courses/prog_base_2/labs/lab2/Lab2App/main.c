#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "queue.h"

typedef int (*cmp_f)(queue_t * self);
typedef void (*react_f)(queue_t * self);

typedef struct dynamic_s {
    HANDLE hLib;
    cmp_f cmp;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();
void printStacks(queue_t * self);

int main(void) {
    const int MAX_STACK_SIZE = 20;
    queue_t * queue = queue_new();
    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->cmp) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    puts("Dynamic loaded!\n");
    srand(time(NULL));
    while (queue_getCount(queue) < MAX_STACK_SIZE) {
        queue_add(queue, rand() % 30);

        printStacks(queue);
        if(dll->cmp(queue)) {
            dll->react(queue);
        }
        printStacks(queue);
    }
    queue_free(queue);
    dynamic_clean(dll);
    return 0;
}

const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        puts("Choose DLL to load:\n\n1. Lab2DLL1\n2. Lab2DLL2\n");
        printf("Your DLL: ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "Lab2DLL1.dll";
        } else if (dllNum == 2) {
            return "Lab2DLL2.dll";
        }
    }
    return NULL;
}

void printStacks(queue_t * self) {
    printf("Queue: ");
    queue_print(self);
    puts("");
    Sleep(1000);
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->cmp = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->cmp = (cmp_f)GetProcAddress(dyn->hLib, "compare");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
