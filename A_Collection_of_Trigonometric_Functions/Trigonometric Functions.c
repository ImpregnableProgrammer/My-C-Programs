/* Trigonometric Functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> /* Only included for access to built-in Sin, Cos, and Tan functions to compare my functions' answers to */
#define PI 3.141592653589793238462643383279502884

double Remainder(double y,double k){
  double x = 0;
  double j = 0;
  while(y>=k){
    x += k;
    if((x+k)>y){
	y -= x;
	x = 0;
      }
  }
  return y;
}

double factorial(int j){
  double y = 1;
  for(int i = 2; i <= j; i++){
    y *= i;
  }
  return y;
}

double power(double k,int b){
  float y = k;
  for(int o = 2; o <= b; o++){
    k *= y;
  }
  k = b==0 ? 1 : b==1 ? y : k;
  return k;
}
 
double Sin_x(double u){
  double l = 0;
  for(int y = 0; y < 10; y++){
    l += (power(-1,y)/factorial(2*y+1))*power(u,2*y+1);
  }
  return l;
}

double Cos_x(double u){
  double l = 0;
  for(int y = 0; y < 10; y++){
    l += (power(-1,y)/factorial(2*y))*power(u,2*y);
  }
  return l;
}

double Tan_x(double u){
  return(Sin_x(u)/Cos_x(u));
}

int main(int argc, char *argv[]){
  float u;
  u = atof(argv[1]);
  float T = u;
  u = atof(argv[2])==1.0 ? (u*PI)/180 : u;
  u = Remainder(u,PI*2);
  char *y = atof(argv[2])==1.0 ? "degrees" : "radians";
  if(strcmp(argv[3],"Sin")==0){
      printf("Sin(%f) in %s from function = %.15f\nSin(%f) in %s from built-in = %.15f\n",T,y,Sin_x(u),T,y,sin(u));
  }
  else if(strcmp(argv[3],"Cos")==0){
      printf("Cos(%f) in %s from function = %.15f\nCos(%f) in %s from built-in = %.15f\n",T,y,Cos_x(u),T,y,cos(u));
  }
  else if(strcmp(argv[3],"Tan")==0){
      printf("Tan(%f) in %s from function = %.15f\nTan(%f) in %s from built-in = %.15f\n",T,y,Tan_x(u),T,y,tan(u));
  }
  return 0;
}

      
  
    
    
