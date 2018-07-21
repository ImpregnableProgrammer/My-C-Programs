//
// This Challenge: https://codegolf.stackexchange.com/questions/87496/alphabet-triangle/87527#87527
#include <stdio.h>
/* int main(){
  char a[27];
  for(int i=65;i<91;i++){
    a[i-65]=(char)i;
  }
  for(int w=0;w<53;w++){
    int g=w>26 ? 26-(w-26):w;
    char j[2*g+1];
    j[2*g+1]='\0';
    int x=0;
    for(int q=0;q<g+g+1;q++){
      j[x]=a[q>=g ? g-(q-g):g];
      printf("%d\n",q);
      x++;
    }
    for(int b=g;b>=0;b--){
      j[x]=a[b];
      x++;
      }
    if(w<26||w>27){
      printf("%s\n",j);
    }
  }
} */

int main(){
  for(int q=0;q<51;q++){
    int i=q>25 ? 25-(q-25):q;
    for(int e=65;e<=65+i;e++){
      printf("%c",e);
    }
    for(int x=65+i-1;x>64;x--){
      printf("%c",x);
    }
    printf("\n");
  }
}


  
