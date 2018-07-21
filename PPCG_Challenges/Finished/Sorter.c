#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** Lexicographical_Sort(int s,char**a) {
  for(int l=0;l<s;++l) {
    for(int j=l+1;j<s;++j) {
      if(strcasecmp(a[l],a[j])>0) {
	char* G = a[j];
	a[j] = a[l];
	a[l] = G;
      }
    }
  }
  return a;
}

int main(int argc, char**argv) {
  char** D = malloc(argc - 1);
  for(int u=0;u<argc-1;u++) {
    D[u] = argv[u+1];
  }
  D = Lexicographical_Sort(argc-1,D);
  printf("[");
  for(int b = 0;b < argc-2;b++) {
    printf("%s, ",D[b]);
  }
  printf("%s]\n",D[argc-2]);
}
    
