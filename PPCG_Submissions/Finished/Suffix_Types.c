// This Challenge: https://codegolf.stackexchange.com/a/127313/52405
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Golfed @ 88 bytes
S(S,A,I)char*S,*A;{for(;strlen(S)>0;A=S,S++,printf("%c",I=strcmp(A,S)>0?76:I==76?42:83));}

int main(int argc, char** argv) {
  S(argv[1]);
}
