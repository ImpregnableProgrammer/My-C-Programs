// This Challenge: https://codegolf.stackexchange.com/questions/60896/naming-non-cyclic-carbon-chains
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* Prefix(int p) {
  return p==1?"meth":p==2?"eth":p==3?"prop":p==4?"but":p==5?"pent":p==6?"hex":p==7?"hept":p==8?"oct":p==9?"non":p==10?"dec":p==11?"undec":p==12?"dodec":"";
}

int q=0;
void Recurse_Chains(char** String, int h, int x, int y, int xp, int yp, int c) {
  printf("x = %d, y = %d, c = %d\n",x,y,c);
  q=c>q?c:q;
  String[x][y]=48+c;
  if(x+2<h&&String[x+1][y]=='|'&&x+2!=xp) {
    // printf("hi1\n");
    Recurse_Chains(String,h,x+2,y,x,y,c+1);
    // printf("c = %d\n",c);
    for(int u=0;u<h;u++) {
      printf("%s\n",String[u]);
    }
  }
  if(y+2<strlen(String[x])&&String[x][y+1]=='-'&&y+2!=yp) {
    // printf("hi2\n");
    Recurse_Chains(String,h,x,y+2,x,y,c+1);
    // printf("c = %d\n",c);
    for(int u=0;u<h;u++) {
      printf("%s\n",String[u]);
    }
  
  }
  if(x-2>=0&&String[x-1][y]=='|'&&x-2!=xp) {
    // printf("hi3\n");
    Recurse_Chains(String,h,x-2,y,x,y,c+1);
    // printf("c = %d\n",c);
    for(int u=0;u<h;u++) {
      printf("%s\n",String[u]);
    }
  }
  if(y-2>=0&&String[x][y-1]=='-'&&y-2!=yp) {
    // printf("hi4\n");
    Recurse_Chains(String,h,x,y-2,x,y,c+1);
    // printf("c = %d\n",c);
    for(int u=0;u<h;u++) {
      printf("%s\n",String[u]);
    }
  }
}

void Name(char** Molecule, int h) {
  int p=0;
  for(int j=0;j<h;j++) {
    for(int o=0;o<strlen(Molecule[j]);o++) {
      if((j-1>=0&&Molecule[j-1][o]=='|')+(o+1<strlen(Molecule[j])&&Molecule[j][o+1]=='-')+(j+1<h&&Molecule[j+1][o]=='|')+(o-1>=0&&Molecule[j][o-1]=='-')==1){
	printf("Up: %d, Right: %d, Down: %d, Left: %d\n",
	       (j-1>=0&&Molecule[j-1][o]=='|'),
	       (o+1<strlen(Molecule[j])&&Molecule[j][o+1]=='-'),
	       (j+1<h&&Molecule[j+1][o]=='|'),
	       (o-1>=0&&Molecule[j][o-1]=='-'));
	Recurse_Chains(Molecule,h,j,o,0,0,1);
	p=q>p?q:p;
	// printf("Molecule[0] = %s\n",Molecule[0]);
	printf("okay!\n");
      }
    }
  }
  char* Name=malloc(8);
  sprintf(Name,"%sane",Prefix(p));
  printf("Name = %s\n",Name);
}

int main(int argc,char**argv) {
  argv++;
  argc--;
  // xv = (int*)malloc(sizeof(int));
  Name(argv,argc);
  // printf("%d\n",sizeof(int*));
  // printf("q = %d\n",q);
}
  
