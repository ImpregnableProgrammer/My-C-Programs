// This Challenge: http://codegolf.stackexchange.com/questions/99685/draw-diagonal-lines-of-text
#include <stdio.h>
#include <string.h>

void Diagonal(char**w){
  int H;
  for(int i=0;i<strlen(w);i++){
    printf("%*c\n",(i%3)+1,w[1][i]);
  }
}

int main(int agc,char**argv){
  Diagonal(argv);
}
