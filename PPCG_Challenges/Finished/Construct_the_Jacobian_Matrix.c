// This Challenge: https://codegolf.stackexchange.com/questions/87532/construct-the-jacobian-matrix/87594#87594
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char*argv[]){
  int y=atoi(argv[2]);
  for(int b=0;b<atoi(argv[1]);b++){
    for(int q=0;q<y;q++){
      printf("d f%d/du u%d%s",b,q,q<y-1 ? ", ":"");
    }
    printf("\n");
  }
}
  
  
