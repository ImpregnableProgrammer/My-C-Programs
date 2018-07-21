//
// This Challenge: https://codegolf.stackexchange.com/questions/133088/your-uncle-help-drunk-needs
//

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
  argc--;
  argv++;
  for(int v=0;v<argc;++v) {
    for(int i=v;i<argc;++i) {
      int p=0;
      char* X=argv[v];
      int G=strlen(X);
      char* L=argv[i];
      int Y=strlen(L);
      for(int m=0,n=0;m<G>=Y?G:Y;++m,++m) {
	if(X[m]==X[n]){
	  ++p;
	}
      }
      p=p<1?-1:p;
