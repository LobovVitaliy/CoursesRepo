#include <stdio.h>
#include <stdlib.h>

void fprocess(const char * pread, const char * pwrite) {

    char str[250];
    int result;
    int i;

    FILE * file1 = fopen(pread, "r");
    FILE * file2 = fopen(pwrite, "w");

    if (file1 == NULL) {
        printf("Error");
    }

    for (i = 0; i < 25; i++) {
        fgets(str, 250, file1);

        if(i==10) {
            result = (int)roundf(atof(str));
            printf("%i\n", result);
            fprintf(file2, "%i", result);
        }
    }

    fclose(file1);
    fclose(file2);
}
