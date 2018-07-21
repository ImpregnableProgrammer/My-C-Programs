#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void Cornu(int N){
  printf("# ImageMagick pixel enumeration: 1000.0,1000.0,255,rgb\n");
  for(float n=0;n<=N;++n){
    int V=2000000;float G=sqrt(pow((n/(N-.5))+.5,2)+V)*V;
    printf("%f,%f:(110,120,450)\n",cos(G*V),sin(G*V));
  }
}

int main(int argc,char**argv){
  Cornu(atoi(argv[1]));
}
