// This Challenge: https://codegolf.stackexchange.com/a/100667/52405
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ungolfed Version
void Matrix(char*a,char*b){
  char*P[2];
  P[0]=malloc(strlen(a));
  P[1]=malloc(strlen(b));
  for(int A=0;A<strlen(a);A++){
    P[0][A]=a[A];
  };
  for(int B=0;B<strlen(b);B++){
    P[1][B]=b[B];
  };
  int H[200][200],B[200][200];
  int O,N,m,J;
  for(int Y=0;Y<2;Y++){
    int y=0,z=0,r=0;
    char j[10];
    int p=strlen(P[Y]);
    for(int i=0;i<=p;i++){
      if(P[Y][i]==' '||P[Y][i]==','||i==p){
	(Y<1)?H[y][z]=atoi(j):(B[y][z]=atoi(j));
	memset(j,'\0',10);
	(P[Y][i]==' ')?z++:y++;
	z=(P[Y][i]==',')?0:z;
	r=0;
      }
      else{
	j[r]=P[Y][i];
	r++;
      };
    };
    (Y<1)?O=z+1,N=y:(m=y,J=z+1);
  };
  for(int U=0;U<N;U++){
    for(int F=0;F<J;F++){
      int T=0;
      for(int d=0;d<O;d++){
	T+=H[U][d]*B[d][F];
      };
      printf("%d ",T);
      T=0;
    };
    printf("\n");
  };
};


// Golfed Version
/*void Matrix(char*a,char*b){char*P[2];P[0]=malloc(strlen(a));P[1]=malloc(strlen(b));for(int A=0;A<strlen(a);A++){P[0][A]=a[A];};for(int B=0;B<strlen(b);B++){P[1][B]=b[B];};int H[200][200],B[200][200];int O,N,m,J;for(int Y=0;Y<2;Y++){int y=0,z=0,r=0;char j[7];int p=strlen(P[Y]);for(int i=0;i<=p;i++){if(P[Y][i]==' '||P[Y][i]==','||i==p){(Y<1)?H[y][z]=atoi(j):(B[y][z]=atoi(j));memset(j,'\0',4);(P[Y][i]==' ')?z++:y++;z=(P[Y][i]==',')?0:z;r=0;}else{j[r]=P[Y][i];r++;};};(Y<1)?O=z+1,N=y:(m=y,J=z+1);};for(int U=0;U<N;U++){for(int F=0;F<J;F++){int T=0;for(int d=0;d<O;d++){T+=H[U][d]*B[d][F];};printf("%d ",T);T=0;};printf("\n");};}*/

int main(int argc,char**argv){
  Matrix(argv[1],argv[2]);
}
