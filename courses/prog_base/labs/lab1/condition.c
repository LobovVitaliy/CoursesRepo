#include <math.h>

int satisfies(int a, int b, int c) {
   int result;
   
   int modmin,sum2;
   int min,max;

   //Якщо числа від'ємні
   if ((a<0) && (b<0) && (c<0))
    {
     if ((a<=b) && (a<=c))
      {
       modmin=abs(a);
       sum2=b+c;
      }
     else
     if ((b<=a) && (b<=c))
      {
       modmin=abs(b);
       sum2=a+c;
      }
     else
      {
       modmin=abs(c);
       sum2=a+b;
      }

     if ((sum2<-256) && ((modmin==1)||(modmin==2)||(modmin==4)||(modmin==8)||(modmin==16)||(modmin==32)||(modmin==64)||(modmin==128)))
      result=1;
     else
   //Якщо не степінь двійки
     if (((abs(sum2)-modmin)<16) || (abs(sum2)<16))
      result=1;
     else
      result=0;
    }
   else
   //Якщо не всі числа додатні
   //Якщо тільки одне число від'ємне
   if ((a<0)&&(b>=0)&&(c>=0) && (a>-256))
    result=1;
   else
   if ((b<0)&&(a>=0)&&(c>=0) && (b>-256))
    result=1;
   else
   if ((c<0)&&(a>=0)&&(b>=0) && (c>-256))
    result=1;
   else
   //Якщо два від'ємних числа
   if ((a<0)&&(b<0)&&(c>=0) && (((a+b)*2)>-256))
    result=1;
   else
   if ((a<0)&&(c<0)&&(b>=0) && (((a+c)*2)>-256))
    result=1;
   else
   if ((b<0)&&(c<0)&&(a>=0) && (((b+c)*2)>-256))
    result=1;
   else
   //Якщо всі числа додатні
   if ((a>=0)&&(b>=0)&&(c>=0))
    {
     //Шукаємо min
     if ((a<=b) && (a<=c))
      min=a;
     else
     if ((b<=a) && (b<=c))
      min=b;
     else
      min=c;
     //Шукаємо max
     if ((a>=b) && (a>=c))
      max=a;
     else
     if ((b>=a) && (b>=c))
      max=b;
     else
      max=c;

     if ((max+min)<256)
      result=1;
     else
      result=0;
    }
   else
    return 0;
    
   return result;
}