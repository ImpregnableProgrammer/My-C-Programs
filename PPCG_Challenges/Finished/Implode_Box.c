// This Challenge: https://codegolf.stackexchange.com/a/125808/52405
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Ungolfed Version
void Imploder(char** Box, int height) {
  int V=strlen(Box[0]);
  int S=0;
  int J=0;
  char**Z=malloc(8);
  for(int i=0,j=height-1;i<height/2+height%2;i++,j--) {
    for(int l=0,n=V-1;l<V/2+V%2;l++,n--) {
      if(Box[i][l]!='+'&&((Box[i][l-1]!='+'&&i<1)||(Box[i-1][l]!='+'&&l<1))) {
	int H=Box[i][l]=='-';
	int W=Box[i][l]=='|';
	char c;
	Box[i][l]=' ';
        Box[j][l]=' ';
        Box[i][n]=' ';
        Box[j][n]=' ';
	if(H) {
	  if(j-l+1<0){
	    char*L=malloc(8);
	    sprintf(L,"%*s",V,"");
	    L[l]=c;
	    L[n]=c;
	    Z[J]=L;
	    J++;
	  }
	  else{
	    c=(i+l-1)==(j-l+1)?'=':'-';
	    Box[i+l-1][l]=c;
	    Box[i+l-1][n]=c;
	    Box[j-l+1][l]=c;
	    Box[j-l+1][n]=c;
	  }
	}
	if(W) {
	  c=(l+i-1)==(n-i+1)?'"':'|';
	  if(n-i+1<0) {
	    char*G=malloc(8);
	    sprintf(G,"|%*s%s%*s|",i-n-2,"",Box[i],i-n-2,"");
	    Box[i]=G;
	    Box[j]=G;
	    S++;
	  }
	  else {
	    Box[i][l+i-1]=c;
	    Box[j][l+i-1]=c;
	    Box[i][n-i+1]=c;
	    Box[j][n-i+1]=c;
	  }
	}
      }
    }
  }
  for(int a=J-1;a>-1;a--){
    int C=S+1-strlen(Box[a])/2;
    printf("%*s%s\n",C>0?C:0,"",Z[a]);
  }
  for(int z=0;z<height;z++) {
    int C=S+1-strlen(Box[z])/2;
    printf("%*s%s\n",C>0?C:0,"",Box[z]);
  }
  for(int _=0;_<J;_++) {
    int C=S+1-strlen(Box[_])/2;
    printf("%*s%s\n",C>0?C:0,"",Z[_]);
  }
}

//Golfed Version @ 693 bytes (Disregarding new lines)
#define P B[i][l]
#define m malloc(8)
I(B,h,V,S,J,Z,i,j,l,n,H,W,c,C,a,z,_,L,G,u,N,M)char**B,**Z;char*L,*G,*u;{
V=strlen(B[0]);
S=J=0;
Z=m;
for(i=0,j=h-1;i<h/2+h%2;i++,j--){
for(l=0,n=V-1;l<V/2+V%2;l++,n--){
if(P!=43&&((B[i][l-1]!=43&&i<1)||(B[i-1][l]!=43&&l<1))){
H=P==45;
W=P=='|';
P=B[j][l]=B[i][n]=B[j][n]=32;
if(H){
c=(N=i+l-1)==(M=j-l+1)?61:45;
if(M<0)L=m,sprintf(L,"%*s",V,""),L[l]=L[n]=c,Z[J]=L,J++;
else B[N][l]=B[N][n]=B[M][l]=B[M][n]=c;
}
if(W){
c=(N=l+i-1)==(M=n-i+1)?34:'|';
if(M<0)G=m,sprintf(G,"|%*s%s%*s|",i-n-2,"",B[i],i-n-2,""),B[i]=B[j]=G,S++;
else B[i][N]=B[j][N]=B[i][M]=B[j][M]=c;
}
}
}
}
for(a=-J+1;a<=h+J;u=a<1?Z[-a]:a<=h?B[a-1]:Z[a-h-1],C=S+1-strlen(u)/2,printf("%*s%s\n",C>0?C:0,"",u),a++);
}

int main(int argc,char**argv) {
  argv++;
  argc--;
  I(argv,argc);
}
