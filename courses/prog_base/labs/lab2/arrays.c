#include <math.h>
#include <stdlib.h>

void fillRand2(int arr[], int size) {
int i;

for (i=0;i<size;i++)
    arr[i] = -255+ rand()%511;
}

int checkRand2(int arr[], int size) {
int i;
int k=0;

for (i=0;i<size;i++){
    if (arr[i]>=-255 && arr[i]<=255)
        k++;
}
if (k==(size))
    return 1;
else
    return 0;
}

float meanValue(int arr[], int size) {
int i;
float m,s=0;

for (i=0;i<size;i++){
    s+=arr[i];
}
m=s/size;
return m;
}

int maxValue(int arr[], int size) {
int i;
int max=arr[0];

for (i=0;i<size;i++){
    if (max<=arr[i])
        max=arr[i];
}
return max;
}

int meanIndex(int arr[], int size) {
    int i;
    int l;
    float m,s=0;

    for (i=0;i<size;i++){
        s+=arr[i];
    }
    m=s/size;

    float raz;
    raz=abs(arr[0]-m);

    for (i=size-1;i>=0;i--){
        if (abs(arr[i]-m)<=raz) {
            raz=abs(arr[i]-m);
            l=i;
        }
    }
return l;
}

int maxIndex(int arr[], int size) {
int i,l;
int max1=arr[0];

for (i=size-1;i>=0;i--){
    if (max1<=arr[i]) {
        max1=arr[i];
        l=i;
    }
}
return l;
}

int maxOccurance(int arr[], int size){
    int i,j,x,a,maximum,z,d;
    int z1=1,y=size-1;

    int max=arr[0];

    for (i=0;i<size;i++){
        if (max<=arr[i])
        max=arr[i];
    }

    for (i=0;i<y;i++) {
        maximum=arr[i];
        d=i+1;
        z=1;
        for (j=d;j<size;j++) {
            if (maximum==arr[j]) {
                z++;
            }
        }
        if (z1==z && z!=1) {
            if (arr[i]>x){
                x=arr[i];
            }
        }
        a=z;
        if (a>z1) {
            z1=a;
            x=arr[i];
        }
    }

    int q=0;

    for (i=0;i<size;i++) {
        if (x!=arr[i]) q++;
    }
    if ( q==size)
        return max;
      else
        return x;
}

int diff(int arr1[], int arr2[], int res[], int size) {
int i;
int k=0;

for (i=0;i<size;i++) {
    res[i]=arr1[i]-arr2[i];
    if (res[i]==0)
        k++;
}
if (k==size)
    return 1;
else
    return 0;
}

void sub(int arr1[], int arr2[], int res[], int size) {
int i;

for (i=0;i<size;i++) {
    res[i]=arr1[i]-arr2[i];
}
}

int lt(int arr1[], int arr2[], int size) {
int i,k=0;

for (i=0;i<size;i++) {
    if (arr1[i]<arr2[i])
        k++;
}
if(k==size)
    return 1;
else
    return 0;
}

void lor(int arr1[], int arr2[], int res[], int size){
int i;

for (i=0;i<size;i++) {
    if (arr1[i]==0 && arr2[i]==0)
        res[i]=0;
    else
        res[i]=1;
}
}
