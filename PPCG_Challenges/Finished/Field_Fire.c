//
// This Challenge: https://codegolf.stackexchange.com/a/138095/52405
//
#include <stdio.h>
#include <string.h>

// Ungolfed
#define F B[i][v]
M(int A,char**B){
  int k,y,m,U,i,v;
  do{
    k=y=0;
    for(i=0;i<A;puts(""),++i){
      for(v=0;v<(m=strlen(B[i]));F=(U=F)>48&&F<56?F+1:F>55?65:(i+1<A&&B[i+1][v]==51||v+1<m&&B[i][v+1]==51||v-1>-1&&B[i][v-1]==52||i-1>-1&&B[i-1][v]==52)&&U<49?49:F,printf("%c",U),k+=U<49||U>64,y++,++v);
    }
    puts("");
  }while(k-y);
}

// Golfed @ 291 bytes
#define F B[i][v]
m(A,B,k,y,m,U,i,v)char**B;{do{for(i=k=y=0;i<A;puts(""),++i)for(v=0;v<(m=strlen(B[i]));F=(U=F)>48&&F<56?F+1:F>55?65:(i+1<A&&B[i+1][v]==51||v+1<m&&B[i][v+1]==51||v-1>-1&&B[i][v-1]==52||i-1>-1&&B[i-1][v]==52)&&U<49?49:F,putchar(U),k+=U<49||U>64,++y,++v);puts("");}while(k-y);}

int main(int argc, char** argv) {
  argc--;
  argv++;
  m(argc,argv);
}
