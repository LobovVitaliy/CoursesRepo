#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {

long long number;
int S,i,j;
double F=0,E=0,V;

scanf("%lld", &number);

S=(number>>63)&1;
for (j=52;j<63;++j) {
    E+=((number>>j)&1)*(pow(2,(j-52)));
}
//printf ("S=%i\nE=%i\n",S,E);
for (i=51;i>=0;--i) {
    F+=((number>>i)&1)*(pow(2,(i-52)));
}
//printf("F=%.325llf\n",F);
if (E==2047 && F!=0)
    printf ("V=NAN");
else
if (E==2047 && F==0 && S==1)
    printf ("V=-Infinity");
else
if (E==2047 && F==0 && S==0)
    printf ("V=Infinity");
else
if (E>0 && E<2047) {
    V=pow(-1,S)*pow(2,E-1023)*(1+F);
    printf("\nV=%.325llf\n",V);
}
else
if (E==0 && F!=0) {
    V=pow(-1,S)*pow(2,-1022)*F;
    printf("\nV=%.325llf\n",V);
}
else
if (E==0 && F==0 && S==1) {
    printf("V=-0");
}
else
if (E==0 && F==0 && S==0){
    printf("V=0");
}
}


