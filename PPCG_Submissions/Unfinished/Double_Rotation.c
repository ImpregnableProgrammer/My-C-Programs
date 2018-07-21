// This Challenge: http://codegolf.stackexchange.com/questions/92305/double-rotation
#include <stdio.h>
#include <string.h>
int main(int argv,char**argc){
  for(int i=0;i<strlen(argc[1]);++i){
    sprintf(str,"%d",argc[1][i]);
    puts(str);
    //if(sprintf("%d\n",argc[1][i])<109){
    //printf("Yeah!");
    //++ptr;
    //*ptr=(char*)i;
    //printf("%s\n",*ptr);
  }
  return 0;
}
