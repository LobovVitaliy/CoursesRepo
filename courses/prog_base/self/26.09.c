{
int h,m,code;
float x;
scanf("%i %i %i",&h,&m,&code);
switch (code)
 {
  case 44: x=((h*60)+m)*0.44; break;
  case 66: x=0; break;
  case  1: x=((h*60)+m)*30; break;
  default: x=((h*60)+m); break;
 }
 printf ("Кількість грошей: %f",x);
 return 0;
}