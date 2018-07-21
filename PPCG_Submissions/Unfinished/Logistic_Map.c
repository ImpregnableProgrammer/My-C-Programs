// This Challenge: https://codegolf.stackexchange.com/questions/123345/the-strange-attraction-of-the-logistic-map
#include <stdio.h>
#include <stdlib.h>

void Attractor(int N,float r_1,float r_2,float s) {
  for(;r_1<=r_2;r_1+=s) {
    float x_0=0.5;
    printf("r = %f\n",r_1);
    for(int i=0;i<N;i++) {
      x_0=r_1*x_0*(1-x_0);
    }
    printf("x_N = %f\n\n",x_0);
  }
}

int main(void) {
  Attractor(1000,1.0,4.0,0.001);
}
