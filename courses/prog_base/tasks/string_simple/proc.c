#include <string.h>
#include <stdio.h>

char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr) {
    char * vowel = "AEIOUYaeiouy";
    int i,j,s=0;
    int len,maxlen = strlen(textLines[0]);
    int k;
    int res;

    for (i=0;i<linesNum;i++) {
        for (j=0;j<strlen(vowel);j++)
            if (*textLines[i]==vowel[j])
                s++;
    }

    for (i=0;i<linesNum;i++) {
        k=0;
        for (j=0;j<strlen(vowel);j++)
            if (*textLines[i]!=vowel[j])
                k++;

        if (k==12)
            len = strlen(textLines[i]);
        else
            continue;

        if (maxlen<=len){
            maxlen = len;
            res = i;
        }
    }

    sprintf(resultStr,"%i",s);
    strcat(resultStr," ");
    strcat(resultStr,textLines[res]);

return resultStr;
}







