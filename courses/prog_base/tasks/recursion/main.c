#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

double rez (double sum) {

    if (sum > 9) {
        sum = sum / 10;
        sum = rez (sum);
    }

    return sum;
}

double pBeg (char * beg) {
    double i;
    double sum;

    if (NULL == beg) {
        return 0;
    }

    if (isdigit(*beg)) {
        sum = atoi(beg);
        sum = rez (sum);
        i = modf(sum, &sum);
    }
    else
        sum = pBeg (beg + 1);

    return sum;
}

int pEnd (char * end) {
    int sum;

    if (NULL == end) {
        return 0;
    }

    if (isdigit(*end)) {
        sum = atoi(end);
    }
    else
        sum = pEnd (end - 1);

    return sum;
}

int main()
{
    char string[100];
    char * beg = string;
    char * end;

    gets(string);
    end = beg + strlen(string) - 1;

    int sum = pBeg(beg) + pEnd(end);

    printf("\n\nSum = %i\n\n", sum);

    return 0;
}



