//
// This Challenge: https://codegolf.stackexchange.com/questions/109477/life-is-a-maze-we-take-the-wrong-path-before-we-learnt-to-walk/129689#129689
// For now, invoke with `Maze_Setup.bash` instead when testing with provided test cases.
// Currently does NOT ALWAYS output the shortest path
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void Output_Maze(char** Maze, int h) {
  for(int i=0;i<h;i++) {
    for(int k=0;k<strlen(Maze[0]);k++) {
      printf("%c",Maze[i][k]);
    }
  }
}

int Q=0;
void Maze_Recurse(char** Maze, int h, int x, int y, int xo, int yo, int z, char* m,int* xinc, int* yinc,int xorig, int yorig) {
  /*if(x-1>-1&&y-1>-1&&Maze[x-1][y-1]=='+') {
    m+=1;
    printf("x, y = %d, %d with m = %d\n",x,y,m);
    for(int i=0;i<h;i++){
      for(int k=0;k<strlen(Maze[0]);k++){
	printf("%c",i==x&&k==y?'*':Maze[i][k]);
      }
    }
  }*/
  Maze[x][y]='*';
  /*int QU=0,A=0,B=0;
  for(int c=2;c<strlen(m);++c) {
    A=B=0;
    for(int e=0;e<c;++e) {
      A+=m[e]=='>'?1:m[e]=='<'?-1:0;
      B+=m[e]=='v'?1:m[e]=='^'?-1:0;
    }
    if(A==0&&B==0){return;}
    //printf("A,B=%d,%d with m=%s\n",A,B,m);
    }*/
  //printf("x,y=%d,%d\n",x,y);
  //if(Q){Q-=1;return;}
  //printf("x,y = %d,%d\n",x,y);
  //char curr=m[strlen(m)-1];
  //int xinc[4]={curr=='>'||curr=='<'?-1:0,curr=='^'?1:curr=='v'?-1:0,curr=='>'||curr=='<'?1:0,curr=='^'?-1:curr=='v'?1:0};
  //int yinc[4]={curr=='^'||curr=='v'?-1:0,curr=='>'?-1:curr=='<'?1:0,curr=='^'||curr=='v'?1:0,curr=='>'?1:curr=='<'?-1:0};
  //printf("%d, %d and %d, %d and %d, %d and %d, %d\n",xinc[0],yinc[0],xinc[1],yinc[1],xinc[2],yinc[2],xinc[3],yinc[3]);
  //Output_Maze(Maze,h);
  if((x+1==h||x-1<0||y+1==strlen(Maze[0])-1||y-1<0)&&strlen(m)>1) {
    m[z%2?z/2+1:z%2]='\0';
    //printf("m = %s with z = %d\n",z/2+1<100?m:"",z/2+1);
    printf("%s with %d steps\n",m,z%2?z/2+1:z/2);
    //exit(0);
    /*int A=0,B=0;
    for(int c=0;c<strlen(m)-1;++c) {
      A=B=0;
      for(int e=c;e<strlen(m)-1;++e) {
	A+=m[e]=='>'?1:m[e]=='<'?-1:0;
	B+=m[e]=='v'?1:m[e]=='^'?-1:0;
      }
      if(A==0&&B==0){QU=1;}
      printf("A,B=%d,%d\n",A,B);
      }*/
    //Output_Maze(Maze,h);
  }
  //if(QU){return;}
  for(int P=0;P<4;++P) {
    if(Maze[x+xinc[P]][y+yinc[P]]==' '&&!(x+xinc[P]==xo&&y+yinc[P]==yo)) {
      m[z/2]=xinc[P]==1?'v':xinc[P]==-1?'^':yinc[P]==1?'>':yinc[P]==-1?'<':0;
      Maze_Recurse(Maze,h,x+xinc[P],y+yinc[P],x,y,z+1,m,xinc,yinc,xorig,yorig);
    }
  }
  /* if(/\*y-1>-1&&*\/Maze[x+xinc[1]][y+yinc[1]]==' '&&!(x+xinc[1]==xo&&y+yinc[1]==yo)) { */
  /*   m[z/2]=xinc[0]==1?'v':xinc[0]==-1?'^':yinc[0]==1?'>':yinc[0]==-1?'<'; */
  /*   Maze_Recurse(Maze,h,x+xinc[1],y+yinc[1],x,y,z+1,m,xinc,yinc); */
  /* } */
  /* if(/\*x-1>-1&&*\/Maze[x+xinc[2]][y+yinc[2]]==' '&&!(x+xinc[2]==xo&&y+yinc[2]==yo)) { */
  /*   m[z/2]='^'; */
  /*   Maze_Recurse(Maze,h,x+xinc[2],y+yinc[2],x,y,z+1,m,xinc,yinc); */
  /* } */
  /* if(/\*y+1<strlen(Maze[0])&&*\/Maze[x+xinc[3]][y+yinc[3]]==' '&&!(x+xinc[3]==xo&&y+yinc[3]==yo)) { */
  /*   m[z/2]='>'; */
  /*   Maze_Recurse(Maze,h,x+xinc[3],y+yinc[3],x,y,z+1,m,xinc,yinc); */
  /* } */
}

void Maze(char** Maze, int h) {
  int w=strlen(Maze[0]);
  char* b=malloc(300);
  int q=0,Y=0,Z=0,G=0;
  int*U,*K,V,R;
  for(int i=0;i<h;++i) {
    for(int m=0;m<w;m+=i<1||i==h-1?1:w-2) {
      if(Maze[i][m]=='I') {
	Maze[i][m]=i<1||i==h-1?'-':'|';
	b[0]=i<1?'v':i==h-1?'^':m<1?'>':m==w-2?'<':' ';
	Y=i;
	Z=m;
	if(G){
	  Maze_Recurse(Maze,h,Y<1?Y+1:Y==h-1?Y-1:Y,Z<1?Z+1:Z==w-2?Z-1:Z,Y,Z,2,b,U,K,V,R);
	  q=1;
	}
	G=1;
      }
      if(Maze[i][m]==' ') {
	int xinc[4]={i<1?-1:i==h-1?1:0,m<1?-1:m==w-2?1:0,i<1?1:i==h-1?-1:0,m<1?1:m==w-2?-1:0};
	U=xinc;
	int yinc[4]={m<1?-1:m==w-2?1:0,i<1?1:i==h-1?-1:0,m<1?1:m==w-2?-1:0,i<1?-1:i==h-1?1:0};
	K=yinc;
	V=i;
	R=m;
	//printf("%d, %d and %d, %d and %d, %d and %d, %d\n",xinc[0],yinc[0],xinc[1],yinc[1],xinc[2],yinc[2],xinc[3],yinc[3]);
	if(G){
	  Maze_Recurse(Maze,h,Y<1?Y+1:Y==h-1?Y-1:Y,Z<1?Z+1:Z==w-2?Z-1:Z,Y,Z,2,b,xinc,yinc,V,R);
	  q=1;
	}
	G=1;
      }
      if(q){break;}
    }
  }
}

int main(void) {
  char** a;
  char* b=malloc(300);
  int i=-1;
  for(;fgets(b,300,stdin);a[++i]=b,b=malloc(300));
  /*char* X="v<<<v<vv<<v<v>>^>>^^>vvv>>>v>vv<vv<<v<v<^<^^^^<vvvvv<^<v<<v>v>>>>>>>>>^>^>^^^<vv<v<<v<<<^<<^<v<<v>v>>>>>>>>>^>^>^^^<vv<v<<v<<<^<<^<v<<v>v>>>>>>>>>^>^>^^^<vv<v<<v<<<^<<^<v<<v>v>>>>>>>v"; 
  for(int c=0;c<strlen(X)-2;++c) {
    int A=0,B=0;
    for(int e=c;e<strlen(X)-1;++e) {
      A+=X[e]=='>'?1:X[e]=='<'?-1:0;
      B+=X[e]=='v'?1:X[e]=='^'?-1:0;
    }
    printf("A,B=%d,%d\n",A,B);
    }*/
  Output_Maze(a,i+1);
  Maze(a,i+1);
}
