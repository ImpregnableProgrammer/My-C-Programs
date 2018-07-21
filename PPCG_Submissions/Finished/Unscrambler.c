// This Challenge: https://codegolf.stackexchange.com/questions/140782/the-original-number-ii
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define G(x) !strcmp(Words[i],x)

void Unscrambler(char *Str, char *Res) {
  //printf("%s, Str=%s\n","Hi!",Str);
  char Words[9][6] = {"ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE"};
  char *Result=malloc(strlen(Res)+2);
  strcpy(Result,Res);
  char *String=malloc(strlen(Str));
  strcpy(String,Str);
  //printf("Stringw = %s\n",String);
  for(int i=0;i<9;++i) {
    ////printf("Stringo = %s\n",String);
    int P=0;
    for(int j=0;j<strlen(Words[i]);++j) {
      for(int k=0;k<strlen(String);++k) {
	if(String[k]==Words[i][j]) {
	  int S=strlen(String);
	  P+=1;
	  for(int y=k;y<S;++y) {
	    //printf("y=%d\n",y);
	    String[y]=String[y+1];
	    //printf("String=%s\n",String);
	  }
	  break;
	}
      }
    }
    //printf("Strlen Words[i] = %lu, Strlen String = %lu, Words[i] = %s, P = %d, Prev = %s\n",strlen(Words[i]),strlen(String),Words[i],P,Str);
    if(P==strlen(Words[i])) {
      //printf("StringY = %s\n",String);
      char* Repl=
	 G("ONE")?"1"
	:G("TWO")?"2"
	:G("THREE")?"3"
	:G("FOUR")?"4"
	:G("FIVE")?"5"
	:G("SIX")?"6"
	:G("SEVEN")?"7"
	:G("EIGHT")?"8"
	:G("NINE")?"9"
	:"??";
      strcat(Result,Repl); // Replace Repl with Words[i] if word form is desired
      //printf("String = %s, Result = %s\n",String,Result);
      if(strlen(String)<1) {
	printf("Number: %s\n",Result);
	exit(0);
      }
      Unscrambler(String,Result);
      strcpy(Result,Res);
    }
    strcpy(String,Str);
  }
}

int main(int argc, char **argv) {
  Unscrambler("ONEWESTV","");
}
