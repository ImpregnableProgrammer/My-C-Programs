// This Challenge: http://codegolf.stackexchange.com/questions/94933/interpret-loose-ranges
#include <stdio.h>
#include <stdlib.h>

void A(char* B,char* C){
  int F=0;
  while(B[F]!='\0'){
    F+=1;
  }
  char*H=malloc(F*sizeof(char));
  for(int E=0;E<=F;E++){
    if(B[E]=='T'){
      E+=3;
      
    }
  }
}

int main(int argc,char**argv){
  //printf("%c\n",'0'+9);
  //if('6'<58){
  //printf("%c\n",'Y');
  //}
  A(argv[1],argv[2]);
}
