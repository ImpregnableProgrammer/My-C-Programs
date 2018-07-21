// This Challenge: https://codegolf.stackexchange.com/questions/127366/smallest-unused-number-sharing-a-factor
#include <stdio.h>

int Number(int n) {
  //int*Y=malloc(8);
  //Y[0]=2;
  for(int i=1;i<=n;i++) {
    float* I=malloc(8);
    int Q=-1;
    for(float u=i-1;u>1;u--) {
      // printf("u = %f\n",u);
      if(fmod(i/u,1.0)==0.0) {
	Q++;
	I[Q]=i/u;
	printf("factor = %f\n",i/u);
	i=u;
      }
    }
  }
}

int main(void) {
  Number(5);
}
