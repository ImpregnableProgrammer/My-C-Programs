/* This Challenge: http://codegolf.stackexchange.com/questions/97060/calculate-the-permanent-as-quickly-as-possible#97136 */
/* Implements Ryser's algorithm */
#include <stdio.h>
#include "Base_Convertor.h"

int Permanent(int**T,int Y){
  int H;
  for(int k=0;k<Y;++k){
    
  }
}
	
int main(int argc,char**argv){
  //printf("%i\n",argc);
  int Y[argc-1][argc-1];
  for(int i=0;i<argc-1;++i){
    for(int u=1;u<argc;++u){
      Y[u][i]=(argv[u][i]=='-')?(-1):1;
      //printf("%i ",Y[u][i]);
    }
    //printf("\n");
  }
  Permanent(Y,argc-1);
}
  
