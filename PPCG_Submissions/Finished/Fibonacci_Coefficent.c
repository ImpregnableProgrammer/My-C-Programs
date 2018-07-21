// This Challenge: https://codegolf.stackexchange.com/a/88952/52405
#include <stdio.h>
#include <inttypes.h>
uint64_t F(int x){return x<1 ? 0:x==1 ? 1:F(x-1)+F(x-2);}
uint64_t G(int H){uint64_t P=1;for(int B=3;B<=H;B++)P*=F(B);return P;}
main(){
  int U,Y;
  scanf("%d %d",&U,&Y);
  printf("%llu\n",G(U)/(G(U-Y)*G(Y)));
}
