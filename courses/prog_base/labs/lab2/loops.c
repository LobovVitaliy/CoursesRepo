double calc(int n, int m) {
double i,j;
double result,y;

result=0;

for (i=1;i<=n;i++) {
    y=0;
    for (j=1;j<=m;j++) {
        y+=(1+(1/(j+1)));
    }
    result+=i*y;
}
return result;
}