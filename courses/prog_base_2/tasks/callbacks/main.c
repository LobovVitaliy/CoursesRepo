#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <Windows.h>

typedef void (*CallbackInRow)(char com);
typedef void (*Callback)(char com, char command[]);

void detect (CallbackInRow threeInRowCB, Callback threeCB);

void threeInRowCB(char com) {
    printf("threeInRowCB:  Key: %c\n", com);
}

void threeCB(char com, char command[]) {
    int i;

    printf("threeCB:     Last key: %c\n", com);
    printf("             Last keys:   ");
    for (i = 0; i < strlen(command); i++) {
        printf("%c ", command[i]);
    }
    puts("");
}


int main(void)
{
    detect(threeInRowCB, threeCB);
    return 0;
}

void detect (CallbackInRow threeInRowCB, Callback threeCB) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    int work = -1;
    int flag = 0;

    char key;
    char command[10];

    while (key != 'e') {
        key = getch();
        command[i] = key;

        work = 0;

        if((command[i] == command[i - 1]) && (command[i] == command[i - 2])) {
            work = 1;
            threeInRowCB(command[i]);
        }

        for (j = 0; j < i-1; j++) {
            flag = 0;
            for (k = j+1; k < i; k++) {
                for (l = k+1; l < i+1; l++) {
                     if((command[j] == command[l]) && (command[l] == command[k])) {

                        flag = 1;

                        if(work != 1) {
                            command[i+1] = '\0';
                            threeCB(command[k], command);
                        }
                        break;
                    }
                }
                if(flag == 1) break;
            }
        }

        if(i == 9) {
            for(j = 0; j < 9; j++) {
                command[j] = command[j+1];
            }
        }
        else {
            i++;
        }
    }
}


