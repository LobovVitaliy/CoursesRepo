#include <stdio.h>
#include <stdlib.h>

struct Startup {
    int num_people ;
    char st [100];
    long long money;
};

int count(int size, struct Startup arr[size]);
void change(struct Startup * pVar, const char * newValue);
void print(struct Startup * pVar);

int main()
{
    int i,c;
    char com[10];
    char newValue[100];

    int size = 3;
    struct Startup arr[] = { {4,"The first startup",3000000}, {7,"The second startup",4000000}, {5,"The third startup",2000000} };

    for (i = 0; i < size; i++) {
        printf("%i. ", i+1);
		print(&arr[i]);
	}

    printf("Number of startups, in which more than 3 million investments: %i", count(size, arr));
    puts("\n\n");

    while (1) {
        printf("Enter index: ");
        gets(com);

        c = atoi(com);

        if (c < 1 || c > size) {
            printf("Error!!!\n");
            continue;
        }
        else
            break;
    }

        printf("Enter new name: ");
        gets(newValue);

        change(&arr[c-1], newValue);
        puts("\n\n");

        for (i = 0; i < size; i++) {
            printf("%i. ", i+1);
            print(&arr[i]);
        }

    return 0;
}

void print(struct Startup * pVar) {
	printf("Number of people: %i\n", pVar->num_people);
	printf("Startup: %s\n", pVar->st);
	printf("Money: %lld\n", pVar->money);
	puts("");
}

int count(int size, struct Startup arr[size]) {
	int i, sum = 0;

	for (i = 0; i < size; i++) {
		if (arr[i].money >= 3000000) {
			sum++;
		}
	}

	return sum;
}

void change(struct Startup * pVar, const char * newValue) {
	strcpy(pVar->st, newValue);
}
