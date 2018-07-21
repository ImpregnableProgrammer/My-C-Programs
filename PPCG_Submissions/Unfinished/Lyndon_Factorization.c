// This Challenge: https://codegolf.stackexchange.com/questions/127337/lyndon-word-factorization
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Factorization(char* String) {
  char*E=String;
  // F:
  for(int i=1;i<=strlen(String);i++) {
    char* T = strndup(String,i);
    E++;
    printf("T = %s and E = %s\n",T,E);
    for(int u=1;u<=strlen(E);u++) {
      char* S = strndup(E,u);
      printf("S = %s\n",S);
      if(strcmp(T,S)>=0) {
	printf("%s\n%s\n",T,S);
	// String+=strlen(T)+strlen(S);
	// goto F;
      }
    }
  }
}

int main(int argc, char** argv) {
  Factorization(argv[1]);
  printf("%d\n",strcmp("P","&O(;"));
}
    
