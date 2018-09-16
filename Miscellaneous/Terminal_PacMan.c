#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

const int HEIGHT = 50;
const int WIDTH = 50;

const char UP = 'w';
const char RIGHT = 'd';
const char DOWN = 's';
const char LEFT = 'a';

int LINE = HEIGHT - 1;
int COLUMN = WIDTH / 2;
int BLINKYLINE = 2;
int BLINKYCOLUMN = WIDTH - 1;
int PINKYLINE = 3;
int PINKYCOLUMN = WIDTH - 1;
int INKYLINE = 4;
int INKYCOLUMN = WIDTH - 1;
int CLYDELINE = 5;
int CLYDECOLUMN = WIDTH - 1;

typedef struct GHOST {
  int LINE;
  int COLUMN;
  char *COLOR;
  pthread_t *thread;
  int SPEED;
} Ghost;

pthread_t *BlinkyThread;
pthread_t *PinkyThread;
pthread_t *InkyThread;
pthread_t *ClydeThread;

void CleanUp() {
  system("stty sane");
  printf("\033[%d;%dH", HEIGHT + 1, 1);
  exit(0);
}

void moveUp() {
  if(LINE - 1 < 2)
    return;
  printf("\033[%d;%dH \033[%d;%dH*", LINE, COLUMN, LINE - 1, COLUMN);
  LINE--;
}

void moveRight() {
  if(COLUMN + 1 >= WIDTH)
    return;
  printf("\033[%d;%dH \033[%d;%dH*", LINE, COLUMN, LINE, COLUMN + 1);
  COLUMN++;
}

void moveDown() {
  if(LINE + 1 >= HEIGHT)
    return;
  printf("\033[%d;%dH \033[%d;%dH*", LINE, COLUMN, LINE + 1, COLUMN);
  LINE++;
}

void moveLeft() {
  if(COLUMN - 1 < 2)
    return;
  printf("\033[%d;%dH \033[%d;%dH*", LINE, COLUMN, LINE, COLUMN - 1);
  COLUMN--;
}

void* MoveGhost(Ghost* ghost) {
  printf("%s\033[%d;%dH*\033[0m\033[%d;%dH\n", ghost->COLOR, ghost->LINE, ghost->COLUMN, 1, WIDTH);
  for(;;) {
    printf("\033[%d;%dH ", ghost->LINE, ghost->COLUMN);
    if(ghost->LINE != LINE)
      printf("%s\033[%d;%dH*\033[0m", ghost->COLOR, ghost->LINE - LINE < 0 ? ++ghost->LINE : --ghost->LINE, ghost->COLUMN);
    else if(ghost->COLUMN != COLUMN)
      printf("%s\033[%d;%dH*\033[0m", ghost->COLOR, ghost->LINE, ghost->COLUMN - COLUMN < 0 ? ++ghost->COLUMN : --ghost->COLUMN);
    if(ghost->LINE == LINE && ghost->COLUMN == COLUMN)
      CleanUp();
    printf("\033[%d;%dH\n", 1, WIDTH);
    usleep(ghost->SPEED);
  }
  return NULL;
}

void* Blinky(void* null) {
  printf("\033[31m\033[%d;%dH*\033[0m\033[%d;%dH\n", BLINKYLINE, BLINKYCOLUMN, 1, WIDTH);
  for(;;) {
    printf("\033[%d;%dH ", BLINKYLINE, BLINKYCOLUMN);
    if(BLINKYLINE != LINE)
      printf("\033[31m\033[%d;%dH*\033[0m", BLINKYLINE - LINE < 0 ? ++BLINKYLINE : --BLINKYLINE, BLINKYCOLUMN);
    else if(BLINKYCOLUMN != COLUMN)
      printf("\033[31m\033[%d;%dH*\033[0m", BLINKYLINE, BLINKYCOLUMN - COLUMN < 0 ? ++BLINKYCOLUMN : --BLINKYCOLUMN);
    if(BLINKYLINE == LINE && BLINKYCOLUMN == COLUMN)
      CleanUp();
    printf("\033[%d;%dH\n", 1, WIDTH);
    usleep(100000);
  }
  return NULL;
}

void* Pinky(void* null) {
  printf("\033[35m\033[%d;%dH*\033[0m\033[%d;%dH\n", PINKYLINE, PINKYCOLUMN, 1, WIDTH);
  for(;;) {
    printf("\033[%d;%dH ", PINKYLINE, PINKYCOLUMN);
    if(PINKYCOLUMN != COLUMN)
      printf("\033[35m\033[%d;%dH*\033[0m", PINKYLINE, PINKYCOLUMN - COLUMN < 0 ? ++PINKYCOLUMN : --PINKYCOLUMN);
    else if(PINKYLINE != LINE)
      printf("\033[35m\033[%d;%dH*\033[0m", PINKYLINE - LINE < 0 ? ++PINKYLINE : --PINKYLINE, PINKYCOLUMN);
    if(PINKYLINE == LINE && PINKYCOLUMN == COLUMN)
      CleanUp();
    printf("\033[%d;%dH\n", 1, WIDTH);
    usleep(100000);
  }
  return NULL;
}

void MainLoop() {
  system("clear;stty raw");
  
  for(int i=0;i<WIDTH;++i)
    printf("\033[0;%dH-\033[%d;%dH-", i, WIDTH, i);
  for(int i=0;i<HEIGHT;++i)
    printf("\033[%d;0H|\033[%d;%dH|", i, i, HEIGHT);

  printf("\033[%d;%dH*\n", LINE, COLUMN);

  BlinkyThread = malloc(sizeof(pthread_t));
  pthread_create(BlinkyThread, NULL, Blinky, NULL);
  PinkyThread = malloc(sizeof(pthread_t));
  pthread_create(PinkyThread, NULL, Pinky, NULL);
  
  /*
  Ghost *Blinky = malloc(sizeof(Ghost));
  Blinky->LINE = 2;
  Blinky->COLUMN = WIDTH - 1;
  Blinky->COLOR = "\033[31m";
  Blinky->thread = malloc(sizeof(pthread_t));
  Blinky->SPEED = 100000;
  pthread_create(Blinky->thread, NULL, MoveGhost, (void*)Blinky);

  Ghost *Pinky = malloc(sizeof(Ghost));
  Pinky->LINE = 3;
  Pinky->COLUMN = WIDTH - 1;
  Pinky->COLOR = "\033[35m";
  Pinky->thread = malloc(sizeof(pthread_t));
  Pinky->SPEED = 500000;
  pthread_create(Pinky->thread, NULL, MoveGhost, (void*)Pinky);
  */
  
  for(;;) {
    printf("\033[%d;%dH\n", 1, WIDTH);
    char c = getchar_unlocked();
    switch(c) {
    case UP:
      moveUp();
      break;
    case RIGHT:
      moveRight();
      break;
    case DOWN:
      moveDown();
      break;
    case LEFT:
      moveLeft();
      break;
    case 'q':
      CleanUp();
    }
  }
}

void DrawMap() {
  for(int i=0;i<WIDTH;++i)
    printf("\033[0;%dH-\033[%d;%dH-", i, WIDTH, i);
  for(int i=0;i<HEIGHT;++i)
    printf("\033[%d;0H|\033[%d;%dH|", i, i, HEIGHT);
  srandom((int)&DrawMap);
  int HoleLine = 10;
  int HoleCol = 10;
  printf("\033[%d;%dH-", HoleLine, HoleCol);
  int LineLimit = 5;
  int ColLimit = 5;
  int Line = HoleLine;
  int Col = HoleCol;
  int HitLineLimit = 0;
  int HitColLimit = 0;
  int LinesNotFinished = 1;
  int ColsNotFinished = 1;
  do {
    int RandWidth = random() % ColLimit;
    int RandHeight = random() % LineLimit;
    for(int i = 0;i < RandWidth && ColsNotFinished;++i) {
      if(HitColLimit < 1) {
	printf("\033[%d;%dH-\n", Line, ++Col);
	if(Col == ColLimit + HoleCol) {
	  HitColLimit = 1;
	  break;
	}
      } else {
	printf("\033[%d;%dH-\n", Line, --Col);
	if(Col == HoleCol)
	  ColsNotFinished = 0;
      }
    }

    for(int i = 0;i < RandHeight && LinesNotFinished;++i) {
      if(HitLineLimit < 1) {
	printf("\033[%d;%dH|\n", ++Line, Col);
	if(Line == LineLimit + HoleLine) {
	  HitLineLimit = 1;
	  break;
	}
      } else {
	printf("\033[%d;%dH|\n", --Line, Col);
	if(Line == HoleLine)
	  LinesNotFinished = 0;
      }
    }
  } while(Line != HoleLine || Col != HoleCol);  
  
  /*do {
    printf("\033[%d;%dH%c", THoleLine, THoleCol, EdgeChar);
    int RandInt = random();
    int RandInt2 = random();
    int a = THoleLine;
    int b = THoleCol;
    THoleLine += RandInt / 100000.0 - RandInt / 100000 < 0.5 ? -1 : 1;
    THoleCol += RandInt2 / 100000.0 - RandInt2 / 100000 < 0.5 ? -1 : 1;
    if(THoleLine < 2 || THoleLine == WIDTH)
      THoleLine = a;
    if(THoleCol < 2 || THoleCol == HEIGHT)
      THoleCol = b;
    EdgeChar = THoleLine != a ? '|' : '-';
    } while(THoleLine != HoleLine || THoleCol != HoleCol);*/
}
  

int main() {
  MainLoop();
  /*srandom((int)&main);
  int RandInt = random();
  printf("%f\n", RandInt / 10000.0 - RandInt / 10000);*/
  return 0;
}
