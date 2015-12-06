#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {

    char *string = (char*)malloc(sizeof(char) * 100);
	char *symbol = (char*)calloc(1, sizeof(char));
	int *num = (int*)malloc(sizeof(int));
	int *i = (int*)malloc(sizeof(int));
    int *j = (int*)malloc(sizeof(int));

    *num = 0;

	char *sym = {"bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"};

	printf("Enter your string: \n");
	gets(string);

	for (*i = 0; *i < strlen(string); (*i)++) {
        for (*j = 0; *j < strlen(sym); (*j)++) {
            if (string[*i] == sym[*j] ) {
                (*num)++;
            }
        }
	}

	printf("\nNumber of consonant letters in line: %i\n", *num);

	free(string);
	free(symbol);
	free(num);
	free(i);
	free(j);

	return 0;
}
