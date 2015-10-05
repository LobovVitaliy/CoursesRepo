#include <math.h>

double calc(double x, double y, double z) {
   double a;
   if ((x!=y) && (z!=0) && (x!=-y) && (sin(x)!=0))
     a=(pow(x,y+1))/(pow(x-y,1/z))+(y/(2*fabs(x+y)))+(sqrt(fabs((cos(y)/sin(x))+1)));
   else
     return NAN;
   return a;
}