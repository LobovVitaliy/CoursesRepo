#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int mat[4][4];
void fillRand(int mat[4][4]);
void rotateCW180(int mat[4][4]);

int main()
{
int i,j;

printf("Matrix fill with random numbers in range [-999..999]\n");
fillRand(mat);
for (i=0;i<4;i++) {
    for (j=0;j<4;j++) {
        printf ("%i\t",mat[i][j]);
    }
printf("\n");
}

printf("\n");

printf("ClockWise180\n");
rotateCW180(mat);
for (i=0;i<4;i++) {
    for (j=0;j<4;j++) {
        printf ("%i\t",mat[i][j]);
    }
printf("\n");
}

return 0;
}

void fillRand(int mat[4][4]) {
int i,j;
time_t t;
srand(time(&t));

for (i=0;i<4;i++) {
    for (j=0;j<4;j++) {
        mat[i][j] = -999 + rand()%1999;
    }
}
}


void rotateCW180(int mat[4][4]) {
int i,j;

int x,y,k,g;

k=0;
for (i=3;i>=0;i--) {

    x=i-3-k;
    g=0;
    for (j=3;j>=0;j--) {

    y=j-3-g;
    g-=2;
    mat[i][j]=mat[x][y];
    }
    k-=2;
}

}