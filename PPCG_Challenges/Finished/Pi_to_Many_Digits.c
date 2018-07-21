#include <stdio.h>
#include <math.h>

long double Pi(){
  long double a, p;
  a = p = 1.0;
  long double t = 1/4.0;
  long double b = 1/sqrt(2);
  long double pi;
  for(int i = 0; i < 100; i++){
    long double z = (a+b)/2.0;
    b = sqrt(a*b);
    t -= p*pow(a-z,2);
    a = z;
    p *= 2;
    pi = pow(z*2,2)/(4*t);
  }
  return pi;
}

void main(){
  printf("%.100Lf\n",Pi());
}
    
