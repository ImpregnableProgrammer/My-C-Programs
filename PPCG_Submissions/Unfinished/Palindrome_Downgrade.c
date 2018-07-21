//
// This Challenge: https://codegolf.stackexchange.com/questions/147224/downgrade-to-a-palindrome

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ungolfed
void Palindrome_Downgrade(char *String) {
  char *StringM = malloc(strlen(String));
  char *StringR = malloc(strlen(String));
  char *StringRe = malloc(strlen(String));
  for(int i=0;i<strlen(String);++i) {
    for(int y=0;y<=strlen(String)-i;++y) {
      realloc(StringM,strlen(String));
      strcpy(StringM,String);
      realloc(StringRe,strlen(String));
      for(int z=y;z<y+i;++z) {
	StringRe[z-y]=StringM[z];
      }
      for(int k=y;k+i<=strlen(String);++k) {
	StringM[k]=StringM[k+i];
	//printf("StringM = %s\n",StringM);
      }
      //printf("StringM = %s\n",StringM);
      realloc(StringR,strlen(StringM));
      strcpy(StringR,StringM);
      //printf("StringR Start = %s\n",StringR);
      for(int u=0;u<strlen(StringM)/2;++u) {
	char R=StringR[u];
	StringR[u]=StringR[strlen(StringM)-u-1];
	StringR[strlen(StringM)-u-1]=R;
      }
      //printf("StringRe = %s\n",StringRe);
      if(!strcmp(StringM,StringR)) {
	printf("%s\n",StringRe);
	return;
      }
    }
    //printf("StringM = %s\n",StringM);
  }
}

// Golfed @ 307 bytes
#define T malloc(K)
P(S,i,y,z,k,u,L,K,V)char*S;{char*M,*R,*E;K=strlen(S);M=T;R=T;E=T;for(i=0;i<K;++i){for(y=0;y<=K-i;++y){strcpy(M,S);for(z=y;z<y+i;E[z-y]=M[z],++z);for(k=y;k+i<=K;M[k]=M[k+i],++k);V=strlen(M);strcpy(R,M);for(u=0;u<V/2;L=R[u],R[u]=R[V-u-1],R[V-u-1]=L,++u);if(!strcmp(M,R))puts(E),exit(0);}}}

int main(int argc, char **argv) {
  P("aabaab");
}
