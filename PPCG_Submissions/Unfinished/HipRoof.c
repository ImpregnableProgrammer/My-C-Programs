
// Submission to this challenge: https://codegolf.stackexchange.com/questions/92047/render-the-top-down-view-of-a-hip-roof-in-ascii

#include <stdio.h>
#include <stdlib.h>

void HipRoof(char **bitmap) {
  while(*bitmap != NULL) {
    char *line;
    for(int i=0;i<4;i++) {
      line = *bitmap;
      while(*line != '\0') {
	printf("%c\n", *line);
	line++;
      }
    }
    bitmap++;
  }
}

int main(int argc, char **argv) {
  argv += 1;
  char* hi = "hello";
  //printf("%d\n", *argv == NULL);
  HipRoof(argv);
  return 0;
}
