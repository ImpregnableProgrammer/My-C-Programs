#include <stdlib.h>
#include <math.h>

char*C(int n,int b){
  int G=(int)(log((double)n)/log((double)b));
  char*P=malloc(G);
  do{
    P[G]=(n%b<10)?(n%b)+'0':(n%b)+'7';
    n/=b;
    G-=1;
  }while(n>1);
  return P;
}
