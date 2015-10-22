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
int mas[4][4];

for (i=0;i<4;i++) {
    for (j=0;j<4;j++) {
        mas[i][j]=mat[i][j];
    }
}

int k,g,a,b;
k=0;

for (i=3;i>=0;i--) {
    a=i-3-k;
    g=0;
    for (j=3;j>=0;j--) {
    b=j-3-g;
    g-=2;
    mat[i][j]=mas[a][b];
    }
    k-=2;
}
}

void flipV(int mat[4][4]) {
int i,j;
int mas[4][4];

int k,g,a,b;

k=0;
for (i=3;i>=0;i--) {
    a=i-3-k;
    g=0;
    for (j=3;j>=0;j--) {
    b=j-3-g;
    g-=2;
    mas[i][j]=mat[a][b];
    }
    k-=2;
}

int c,d;

d=0;
for (i=3;i>=0;i--) {
    c=i-3-d;
    for (j=0;j<4;j++) {
    mat[i][j]=mas[c][j];
    }
    d-=2;
}
}

void transposSide(int mat[4][4]) {
int i,j;
int c,d;
int mas[4][4];

for (i=0;i<4;i++) {
    for (j=0;j<4;j++) {
        mas[i][j]=mat[i][j];
    }
}

d=0;
for (i=3;i>=0;i--) {
    c=i-3-d;
    for (j=0;j<4;j++) {
    mat[i][j]=mas[c][j];
    }
    d-=2;
}

int mas1[4][4];

for (i=0;i<4;i++) {
    for (j=0;j<4;j++) {
        mas1[i][j]=mat[i][j];
    }
}

int a,b;

for (i=0;i<4;i++) {
         a=3-i;
    for (j=0;j<4;j++) {
            b=3-j;
        mat[i][j]=mas1[b][a];
    }
}
}

