#include <stdio.h>
#include <stdlib.h>

#include "ScrumMaster.h"
#include "parse.h"

// gcc main.c -I include -L  lib -llibxml2

int main()
{
    int size = 3;
    master * scrumMaster[3];

    for (int i = 0; i < size; i++)
    {
        scrumMaster[i] = master_new();
    }

    parse(scrumMaster, "ScrumMaster.xml");

    for (int i = 0; i < size; i++)
    {
        master_print(scrumMaster[i]);
    }

    for (int i = 0; i < size; i++)
    {
        master_free(scrumMaster[i]);
    }

    return 0;
}
