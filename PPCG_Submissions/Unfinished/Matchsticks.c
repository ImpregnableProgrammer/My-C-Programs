// This Challenge: https://codegolf.stackexchange.com/questions/135699/solve-a-matchstick-puzzle
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Solution(char* n, int moves) {
  char* Numbers[10] = {"1110110","0010010","1011101","1011011","0111010","1101011","1101111","1010010","1111111","1111011"};
  //for(int i=0;i<stren(n);++i){
  char*A="";
  for(int i=0;i<10;++i){
    int U=0;
    for(int y=0;y<7;U+=Numbers[n[0]-48][y]-Numbers[i][y]!=0,++y);
    printf("%d with U=%d\n",U>0&&U<=moves?i:-1,U);
  }
}

int main(void) {
  Solution("8",3);
}
