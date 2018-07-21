/* Trigonometric Functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> /* Only included for access to built-in Sin, Cos, and Tan functions to compare my functions' answers to */
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

double Remainder(double y,double k){
  double x = 0;
  double j = 0;
  while(y>=k){
    x += k;
    /* printf("Value of `x`: %f\n",x); */
    if((x+k)>y){
	y -= x;
	/* printf("Value of `y`: %f\n",y); */
	x = 0;
      }
  }
  return y;
}

double factorial(int j){
  printf("Starting factorial with %d...\n",j);
  double y = 1;
  for(int i = 2; i <= j; i++){
    y *= i;
  }
  printf("Finished! Result: %f\n",y);
  return y;
}

double power(double k,int b){
  printf("Starting power with %f and %d...\n",k,b);
  float y = k;
  for(int o = 2; o <= b; o++){
    k *= y;
    printf("In progress with current result %f\n",k);
  }
  printf("Result before decision: %f\n",k);
  k = b==0 ? 1 : b==1 ? y : k;
  printf("Done! Result after decision:%f\n",k);
  return k;
}
 
double Sin_x(double u){
  double l = 0;
  printf("Starting sin...\n");
  for(int y = 0; y < 10; y++){
    printf("Starting Iteration # %d\n",y);
    l += (power(-1,y)/factorial(2*y+1))*power(u,2*y+1);
    printf("In progress with current sin result: %f\n",l);
  }
  printf("Finished!\n");
  return l;
}

double Cos_x(double u){
  double l = 0;
  printf("`L`:%f",l);
  printf("Starting cos...\n");
  for(int y = 0; y < 10; y++){
    printf("Starting Iteration # %d\n",y);
    l += (power(-1,y)/factorial(2*y))*power(u,2*y);
    printf("In progress with current cos result: %f\n",l);
  }
  printf("Finished!\n");
  return l;
}

double Tan_x(double u){
  printf("Sin(x) from Tan: %f\n",Sin_x(u));
  printf("Cos(x) from Tan: %f\n",Cos_x(u));
  return(Sin_x(u)/Cos_x(u));
}

int main(int argc, char *argv[]){
  float u;
  printf("%f\n",1/3.0);
  printf("Arguments: %s and %s\n",argv[1],argv[2]);
  printf("To be value of `u`: %f\n",atof(argv[1]));
  u = atof(argv[1]);
  float T = u;
  printf("Value of `u` before first decision: %f\n",u);
  u = atof(argv[2])==1.0 ? (u*M_PI)/180 : u;
  printf("Value of `u` before second decision: %f\n",u);
  u = Remainder(u,M_PI*2);
  printf("Final Value of `u`: %f\n",u);
  char *y = atof(argv[2])==1.0 ? "degrees" : "radians";
  if(strcmp(argv[3],"Sin")==0){
      printf("Sin(%f) in %s from function = %.15f\nSin(%f) in %s from built-in = %.15f\n",T,y,Sin_x(u),T,y,sin(u));
  }
  else if(strcmp(argv[3],"Cos")==0){
      printf("Cos(%f) in %s from function = %.15f\nCos(%f) in %s from built-in = %.15f\n",T,y,Cos_x(u),T,y,cos(u));
  }
  else if(strcmp(argv[3],"Tan")==0){
      /* printf("Tan(x) from Tan as Sin(x)/Cos(x): %f\n",Sin_x(u)/Cos_x(u)); */
      printf("Tan(%f) in %s from function = %.15f\nTan(%f) in %s from built-in = %.15f\n",T,y,Tan_x(u),T,y,tan(u));
      /* printf("Sin(x) from Tan: %f\n",Sin_x(u));
      printf("Cos(x) from Tan: %f\n",Cos_x(u));
      printf("Tan(x) from Tan as Sin(x)/Cos(x): %f\n",Sin_x(u)/Cos_x(u)); */
  }
  return 0;
}

      
  
    
    
