#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void Calander(){
  char M[24][66];
  for(int y=0;y<24;y++){
    for(int g=0;g<66;g++){
      M[y][g]=((g>0&&g<65&&y<1)||(g>1&&g<64&&y==23))?'_':((g==1&&y==1)||(g==64&&y==23))?'\\':((g==64&&y==1)||(g==1&&y==23))?'/':(2<g&&g<63&&(y==1||y==22))?'_':(((g<1||g>64)&&y>0)||((g==2||g==63)&&(1<y&&y<23)))?'|':' ';
      //M[y][g]=(y<1)?'-':' ';
    }
    printf("%s\n",M[y]);
  }
  time_t TIME;
  time(&TIME);
  struct tm *info=localtime(&TIME);
  char HOUR[80];
  strftime(HOUR,80,"%I",info);
  int Hour=(HOUR[0]=='0')?atoi(&HOUR[1]):atoi(HOUR);
  printf("Hour is %d\n",Hour);
  int D=(rand()+2)
}
  
int main(){
  Calander();
}

  
