#include <stdio.h>

// A simple implementation with a lot of string formatting and for loops
/* int main(int m){
  int e=m-1;
  int O=2*(m-1);
  for(int y=2;y<2*m;y+=2){
    printf("Value of `y`: %d\n",y);
    int p=O%4==0;
    printf("`e`: %d\n",e);
    printf("`p`: %d\n",p);
    printf("`e-1`: %d\n",e-1);
    char x[y-2],d[e],l[e-1-p],u[y];
    x[y-2]=d[e]=l[e-1-p]=u[y]='\0';
    for(int W=0;W<e-1-p;++W)l[W]=' ';
    for(int g=0;g<y;++g)u[g]='_';
    for(int z=0;z<(y-2);++z)x[z]='_';
    for(int s=0;s<e;++s)d[s]=' ';
    printf("%s%s\n%s%s/,%s,\\%s\n",d,u,(O>4)? l:"",p ? "o":"",x,p ? "":"o");
    e--;
    O-=2;
    printf("`u`: %s\n",u);
    printf("`l`: %sOK\n",l);
  }
} */

// This Challenge: http://codegolf.stackexchange.com/questions/87614/turtles-all-the-way-down/88634#88634
//A recursive solution
#include <string.h>
int FE;
void M(int w){
  int j=w;
  if(j<=FE){
    char b[(j*2)-1],k[j*2+1];
    b[(j*2)-2]=k[j*2]=0;
    memset(b,'_',(j*2)-2);
    memset(k,'_',j*2);
    int R=((FE+1-j)%2==0);
    printf("%*s\n%*s/,%s,\\%s\n",(j*2)+(FE+1)-j,k,FE-j,R ? "o":"",b,R ? "":"o");
    j++;
    M(j);
  }
}
int main(int p){
  FE=p-1;
  M(1);
}
  
