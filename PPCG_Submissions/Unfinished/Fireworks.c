// This Challenge: https://codegolf.stackexchange.com/questions/129838/4th-of-july-fireworks
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // For the `timespec` structure and `nanosleep` function

void Fireworks(int w, int h, double prob, int frames) {
  char B[h+1][w+1];
  struct timespec ts;
  ts.tv_sec=0;
  ts.tv_nsec=100*1e6;
  srand(time(NULL));
  for(int i=0;i<=frames;i++) {
    //printf(i>0?"\033[%dA\033[%dD":"",h-1,w-1);
    printf("Hi!\n");
    for(int o=1;o<h;o++) {
      for(int y=1;y<w;y++) {
	char*a=&B[o-1][y-1],*b=&B[o-1][y],*c=&B[o-1][y+1],*d=&B[o][y-1],*e=&B[o][y+1],*f=&B[o+1][y-1],*g=&B[o+1][y],*k=&B[o+1][y+1],*l=&B[o][y];
	if(*l=='*')*a=*a!='*'?'\\':*a,*k=*k!='*'?'\\':*k,*b=*b!='*'?'|':*b,*g=*g!='*'?'|':*g,*c=*c!='*'?'/':*c,*f=*f!='*'?'/':*f,*d=*d!='*'?'-':*d,*e=*e!='*'?'-':*e,*l=6;
	else if(*l==6)*a=*b=*c=*d=*e=*f=*g=*k=*l=' ';
	else *l=*l==' '&&1.0*rand()/RAND_MAX<=prob?'*':i<1?' ':*l;
	//if(*l==' '&&(*k=='\\'||*a=='\\'||*b=='|'||*g=='|'||*c=='/'||*f=='/'||*d=='-'||*e=='-'))*a=*b=*c=*d=*e=*f=*g=*k=*l=' ';
      }
    }
    for(int j=0;++j<h;puts("")){
      for(int q=0;++q<w;printf("%c",B[j][q]!=6?B[j][q]:' '));
    }
    nanosleep(&ts,NULL);
  }
}

int main(void) {
  Fireworks(75,25,0.005,5);
  //printf("%c\n",0);
  /*printf("%c7",27);
  printf("Hello hi!");
  printf("%c8",27);*/
  /*int a=5;
  printf("a = %d\n",a);
  int *b=&a;
  *b=6;
  printf("a = %d\n",a);*/
}

