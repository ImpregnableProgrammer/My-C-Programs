
/*

  ---------------------------------------------------------------------

  Copyright (C) 2018  Rohan Kapur

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  ----------------------------------------------------------------------

  * A simple implementation of Snake for the command line. 
  * Built using ANSI escape sequences for cursor movement, and POSIX threads 
    for multithreading.
  * Runs in the raw terminal environment. 
  * Invoke using `./Terminal_Snake_Game.out`.
  * Use the W, A, S, and D keys for movement.
  * The "SnakeHighScoreFile" file is where the high score is saved.
  
  ANSI escape sequence reference: http://ascii-table.com/ansi-escape-sequences.php

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // For POSIX threading.
#include <unistd.h> // For `usleep`.

const int LINES = 50; // No. of lines in the play area. Default: 50.
const int COLUMNS = 150; // No. of columns in the play area. Default: 150.

// Directional constants
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

// Linked list of the coordinates comprising the snake.
typedef struct SNAKE {
  int line;
  int column;
  int direction;
  struct SNAKE *next;
} *snake;

snake Snake; // The snake.
snake SnakeHead; // The head of the snake.
const char *HeadChar = "\033[47m \033[0m"; // A single character or graphics escape sequence for the head of the snake. Default: "@".
const char *TailChar = "\033[42m \033[0m"; // A single character or graphics escape sequence for the tail of the snake. Default: "O".
const char *AppleChar = "\033[45m \033[0m"; // A single character or graphics escape sequence representing the apple. Default: "A".
const int INITLENGTH = 10; // Initial length of the snake tail. Default: 10.
const int COLCOMPENSATION = 15; // Distance from right border marking the limit of the spawn area for the snake upon initialization. Default: 15.
int APPLE[2]; // Array holding the coordinates of the apple.

int SCORE = 0; // Holds the current score.
FILE *HighScoreFile; // FILE* object to store and retrieve the all-time high score.
int HIGHSCORE = 0; // Holds the current high score.

const int STARTDELAY = 1500000; // Time delay, in microseconds, before the game begins. Default: 1.5 s.
int STEPTIME = 80000; // Time, in microseconds, taken between each step of snake. Default: 80 ms.
const int DELTASTEPTIME = 10000; // The amount of time by which STEPTIME decreases with each point earned. Default: 10 ms.
const int MINSTEPTIME = 30000; // The smallest possible STEPTIME. Default: 30 ms.

pthread_t *thread; // POSIX thread variable.

// Cleanup on exit.
void cleanup() {
  system("stty sane");
  free(Snake);
  printf("\033[%d;1HFinal Score: %d\n", LINES, SCORE);
  if(SCORE > HIGHSCORE) {
    printf("New High Score!\n");
    freopen("SnakeHighScoreFile", "w", HighScoreFile);
    fprintf(HighScoreFile, "%d", SCORE);
  }
  fclose(HighScoreFile);
  exit(0);
}

// Generate a random integer in the range [a, b).
int randIntInRange(int a, int b) {
  int rand = (random() + a) % b;
  return rand < a ? a : rand;
}

// Method to move tail of snake forward in the present direction, as well as checking for collision with self and the apple.
void moveSnake(int line, int column) {
  int PotentialAppleLine = randIntInRange(2, LINES);
  int PotentialAppleColumn = randIntInRange(2, COLUMNS);
  while(PotentialAppleLine == SnakeHead->line && PotentialAppleColumn == SnakeHead->column) {
      PotentialAppleLine = randIntInRange(2, LINES);
      PotentialAppleColumn = randIntInRange(2, COLUMNS);
  }
  
  while(Snake->next) {
    Snake = Snake->next;
    int l = Snake->line;
    int c = Snake->column;
    Snake->line = line;
    Snake->column = column;
    printf("\033[%d;%dH%s\033[%d;%dH ", line, column, TailChar, l, c);
    line = l;
    column = c;
    if(SnakeHead->line == Snake->line && SnakeHead->column == Snake->column)
      cleanup();
    while(PotentialAppleLine == Snake->line && PotentialAppleColumn == Snake->column) {
      PotentialAppleLine = randIntInRange(2, LINES);
      PotentialAppleColumn = randIntInRange(2, COLUMNS);
    }
  }
    
  if(SnakeHead->line == APPLE[0] && SnakeHead->column == APPLE[1]) {
    snake newPart = malloc(sizeof(struct SNAKE));
    newPart->line = line;
    newPart->column = column;
    newPart->next = NULL;
    printf("\033[%d;%dH%s", line, column, TailChar);
    Snake->next = newPart;
    
    while((PotentialAppleLine == Snake->line && PotentialAppleColumn == Snake->column) ||
	  (PotentialAppleLine == APPLE[0] && PotentialAppleLine == APPLE[1]))
      {
	PotentialAppleLine = randIntInRange(2, LINES);
	PotentialAppleColumn = randIntInRange(2, COLUMNS);
      }
    APPLE[0] = PotentialAppleLine;
    APPLE[1] = PotentialAppleColumn;
    printf("\033[%d;%dH%s", APPLE[0], APPLE[1], AppleChar);

    SCORE++;
    STEPTIME -= STEPTIME > MINSTEPTIME ? DELTASTEPTIME : 0;

    printf("\033[0;0HScore: %d", SCORE);
  }

  Snake = SnakeHead;
  printf("\033[%d;%dH\n", 0, COLUMNS);
}

// Directional movement methods.
void moveUp() {
  if(--Snake->line == 1 || Snake->column == 1 || Snake->column == COLUMNS)
    cleanup();
  else
    printf("\033[%d;%dH \033[%d;%dH%s", Snake->line + 1, Snake->column, Snake->line, Snake->column, HeadChar);
  Snake->direction = UP;
  moveSnake(Snake->line + 1, Snake->column);
}

void moveRight(){
  if(++Snake->column == COLUMNS || Snake->line == 1 || Snake->line == LINES)
    cleanup();
  else
    printf("\033[%d;%dH \033[%d;%dH%s", Snake->line, Snake->column - 1, Snake->line, Snake->column, HeadChar);
  Snake->direction = RIGHT;
  moveSnake(Snake->line, Snake->column - 1);
}

void moveDown() {
  if(++Snake->line == LINES || Snake->column == 1 || Snake->column == COLUMNS)
    cleanup();
  else
    printf("\033[%d;%dH \033[%d;%dH%s", Snake->line - 1, Snake->column, Snake->line, Snake->column, HeadChar);
  Snake->direction = DOWN;
  moveSnake(Snake->line - 1, Snake->column);
}

void moveLeft() {
  if(--Snake->column == 1 || Snake->line == 1 || Snake->line == LINES)
    cleanup();
  else
    printf("\033[%d;%dH \033[%d;%dH%s", Snake->line, Snake->column + 1, Snake->line, Snake->column, HeadChar);
  Snake->direction = LEFT;
  moveSnake(Snake->line, Snake->column + 1);
}

// Method that runs in a separate thread and auto-moves the snake forward in the current direction.
void* moveForward(void* null) {
  for(;;) {
    switch(Snake->direction) {
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
    }
    usleep(STEPTIME);
  }
  return NULL;
}

// Main loop of the program, which initializes the program and then is responsible for registering valid keypresses.
void mainLoop() {
  system("clear; stty raw");
  
  for(int i = 2;i < COLUMNS;i++)
    printf("\033[0;%dH-\033[%d;%dH-", i, LINES, i);
  for(int j = 2;j < LINES;j++)
    printf("\033[%d;0H|\033[%d;%dH|", j, j, COLUMNS);
  
  Snake = malloc(sizeof(struct SNAKE));

  srandom((int)(&Snake));

  HighScoreFile = fopen("SnakeHighScoreFile", "r");
  fscanf(HighScoreFile, "%d", &HIGHSCORE);

  APPLE[0] = randIntInRange(2, LINES);
  APPLE[1] = randIntInRange(2, COLUMNS);
  
  Snake->line = randIntInRange(2, LINES);
  Snake->column = randIntInRange(2 + INITLENGTH, COLUMNS - COLCOMPENSATION);
  Snake->direction = RIGHT;
  Snake->next = NULL;
  SnakeHead = Snake;
  while(APPLE[0] == SnakeHead->line && APPLE[1] == SnakeHead->column) {
      APPLE[0] = randIntInRange(2, LINES);
      APPLE[1] = randIntInRange(2, COLUMNS);
  }
  for(int i = 0;i < INITLENGTH; ++i) {
    snake newPart = malloc(sizeof(struct SNAKE));
    newPart->line = Snake->line;
    newPart->column = Snake->column - 1;
    while(APPLE[0] == newPart->line && APPLE[1] == newPart->column) {
      APPLE[0] = randIntInRange(2, LINES);
      APPLE[1] = randIntInRange(2, COLUMNS);
    }
    printf("\033[%d;%dH%s", newPart->line, newPart->column, TailChar);
    newPart->next = NULL;
    Snake->next = newPart;
    Snake = Snake->next;
  }
  Snake = SnakeHead;
  
  printf("\033[0;0HScore: %d---High Score: %d\033[%d;%dH%s\033[%d;%dH%s\033[0;%dH\n", SCORE, HIGHSCORE, APPLE[0], APPLE[1], AppleChar, Snake->line, Snake->column, HeadChar, COLUMNS);

  usleep(STARTDELAY);
  
  thread = malloc(sizeof(pthread_t));
  pthread_create(thread, NULL, moveForward, NULL);

  for(;;) {
    int c = getchar_unlocked();
    switch(c) {
    case 'w':
      if(Snake->direction != UP && !(Snake->direction == DOWN && INITLENGTH > 0))
	moveUp();
      break;
    case 'd':
      if(Snake->direction != RIGHT && !(Snake->direction == LEFT && INITLENGTH > 0))
	moveRight();
      break;
    case 's':
      if(Snake->direction != DOWN && !(Snake->direction == UP && INITLENGTH > 0))
	moveDown();
      break;
    case 'a':
      if(Snake->direction != LEFT && !(Snake->direction == RIGHT && INITLENGTH > 0))
	moveLeft();
      break;
    }
  }
  
  cleanup();
}

int main() {
  mainLoop();
  return 0;
}
