#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *arr = "525.2414";
    int i;

    for (i=0;i<strlen(arr);i++) {
        if (arr[i]==' ') {
            printf("y vas ect probel\n"); break;
        }
            if (arr[i]=='.') {
                printf("Point\n");
            }
    }
    return 0;
}
