// This Challenge: https://codegolf.stackexchange.com/questions/119783/zooming-in-on-a-map
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Zoom(int S,char**Map,int H) {
  for(int p=0,y=0;p<strlen(argv[1]);p++,y+=S) {
    for(int j=y;j<y+S;j++) {
      
