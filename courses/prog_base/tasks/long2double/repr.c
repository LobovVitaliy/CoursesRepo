/*
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double long2double(long long);

int main() {

long long number;
double V;

scanf("%lld", &number);
V = long2double(number);
printf ("%.325llf",V);

return 0;
}
*/

double long2double(long long number) {

int S,i,j;
double F=0,E=0;
double V;

S=(number>>63)&1;
for (j=52;j<63;++j) {
    E+=((number>>j)&1)*(pow(2,(j-52)));
}
for (i=51;i>=0;--i) {
    F+=((number>>i)&1)*(pow(2,(i-52)));
}
if (E==2047 && F!=0)
    return NAN;
else
if (E==2047 && F==0 && S==1)
    return -INFINITY;
else
if (E==2047 && F==0 && S==0)
    return INFINITY;
else
if (E>0 && E<2047) {
    V=pow(-1,S)*pow(2,E-1023)*(1+F);
    return V;
}
else
if (E==0 && F!=0) {
    V=pow(-1,S)*pow(2,-1022)*F;
    return V;
}
else
if (E==0 && F==0 && S==1) {
    return -0.0;
}
else
if (E==0 && F==0 && S==0){
    return 0;
}
}
