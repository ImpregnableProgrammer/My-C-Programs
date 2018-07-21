// This Challenge: https://codegolf.stackexchange.com/a/99689/52405
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void Encode(char*J){
  size_t L=ceil(sqrt(strlen(J)));
  int U;
  srand(time(NULL));
  for(int i=0;i<L;i++){
    for(int f=0;f<L;f++){
      printf("#%02X%02X%02X ",rand()%256,(U<strlen(J))?(int)J[U]:32,rand()%256);
      U+=1;
    }
    printf("\n");
  }
}

void Decode(int c,char**U){
  char T[c];
  for(int Y=1;Y<c;Y++){
    char G[2]={U[Y][3],U[Y][4]};
    T[Y-1]=(char)strtol(G,NULL,16);
  }
  int C=c-1;
  T[C]=' ';
  while(T[C]==' '){
    T[C]='\0';
    C-=1;
  }
  printf("%s\n",T);
}   

int main(int argc,char**argv){
  if(strcmp(argv[1],"E")==0){
     Encode(argv[2]);
  }
  else{
     Decode(argc,argv);
  }
}
