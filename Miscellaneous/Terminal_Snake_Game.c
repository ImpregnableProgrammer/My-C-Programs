
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
  * The "SnakeHighScoreFile" file contains the high score.
  
  ANSI escape sequence reference: http://ascii-table.com/ansi-escape-sequences.php

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // For POSIX threading.
#include <unistd.h> // For `usleep`.

const int LINES = 50; // No. of lines in the play area. DEFAULT: 50.
const int COLUMNS = 50; // No. of columns in the play area. DEFAULT: 50.

// Directional constants. DO NOT CHANGE!!
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
const char *HeadChar = "\033[47m \033[0m"; // A single character or escape sequence for graphics representing the head of the snake. DEFAULT: "@".
const char *TailChar = "\033[42m \033[0m"; // A single character or escape sequence for graphics representing the tail of the snake. DEFAULT: "O".
const char *AppleChar = "\033[45m \033[0m"; // A single character or escape sequence for graphics representing the apple. DEFAULT: "A".
int LENGTH = 5; // Current Length of the snake tail. Value is the starting length. DEFAULT: 5.
const int DELTALENGTH = 5; // Amount by which to extend the snake with each point. DEFAULT: 5.
int EXTEND = 0; // Global variable holding the amount remaining by which the snake is to be lengthened. DO NOT CHANGE!!
const int COLCOMPENSATION = 15; // Distance from right border marking the limit of the spawn area for the snake upon initialization. DEFAULT: 15.
int APPLE[2]; // Array holding the coordinates of the apple.

int SCORE = 0; // Holds the current score. DO NOT CHANGE!!
FILE *HighScoreFile; // A FILE* object to store and retrieve the all-time high score.
int HIGHSCORE = 0; // Holds the current high score. DO NOT CHANGE!!

const int STARTDELAY = 1500000; // Time delay, in microseconds, before the game begins. DEFAULT: 1.5 s.
int STEPTIME = 80000; // Time, in microseconds, taken between each step of snake. DEFAULT: 80 ms.
const int DELTASTEPTIME = 5000; // The amount of time, in microseconds, by which STEPTIME decreases with each point earned. DEFAULT: 5 ms.
const int MINSTEPTIME = 30000; // The smallest possible STEPTIME value, in microseconds. DEFAULT: 30 ms.

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
  pthread_cancel(*thread);
  exit(0);
}

// Generate a random positive integer in the range [a, b).
int randIntInRange(int a, int b) {
  int rand = (random() + a) % b;
  return rand < a ? a : rand;
}

// Return whether the input coordinate is occupied by the snake.
int SpotTaken(int line, int column) {
  snake head = SnakeHead;
  while(head) {
    if(head->line == line && head->column == column)
      return 1;
    head = head->next;
  }
  return 0;
}  
  
// Move the tail of the snake forward in the present direction, and check for collision with the snake as well as the apple.
void moveSnake(int line, int column) {
  /*
  int LineDirection = 0;
  int ColDirection = 0;
  */
  int SelfCollision = 0;
  
  while(Snake->next) {
    Snake = Snake->next;
    int l = Snake->line;
    int c = Snake->column;
    /*
    LineDirection = l - line;
    ColDirection = c - column;
    */
    Snake->line = line;
    Snake->column = column;
    printf("\033[%d;%dH%s\033[%d;%dH ", line, column, TailChar, l, c);
    line = l;
    column = c;
    if(SnakeHead->line == Snake->line && SnakeHead->column == Snake->column)
      SelfCollision = 1;
  }
  
  if(SelfCollision)
    cleanup();

  if(EXTEND) {
    snake newPart = malloc(sizeof(struct SNAKE));
    newPart->line = line;
    newPart->column = column;
    newPart->next = NULL;
    Snake->next = newPart;
    printf("\033[%d;%dH%s", Snake->line, Snake->column, TailChar);
    EXTEND--;
  }
    
  if(SnakeHead->line == APPLE[0] && SnakeHead->column == APPLE[1]) {

    EXTEND += DELTALENGTH;
    
    /* Previous implementation for extending the snake: Extend the snake backwards,
     * compensating (through the long conditional construct) should the tail tip
     * collide with a wall or a part of the snake in the process of extension.
     * The variables `LineDirection` and `ColDirection` were used here, 
     * collectively representing the direction in which the tip of the tail is
     * moving.
     * Works for its purpose, but gives rise to many edge cases, not to mention
     * unreliable gameplay.
     * Now the snake is more simply and efficiently extended with the tail tip 
     * remaining in place.
     */
    /*
    for(int i = 0;i < DELTALENGTH;++i) {
      snake newPart = malloc(sizeof(struct SNAKE));
      newPart->line = Snake->line;
      newPart->column = Snake->column;
      int condition = 0;
      if(LineDirection == -1) {
	condition = Snake->line - 1 < 2 || SpotTaken(Snake->line - 1, Snake->column);
	if(condition && Snake->column < COLUMNS / 2)
	  newPart->column = Snake->column + 1;
	else if(condition)
	  newPart->column = Snake->column - 1;
	else
	  newPart->line = Snake->line - 1;
      }
      else if(ColDirection == -1) {
	condition = Snake->column - 1 < 2 || SpotTaken(Snake->line, Snake->column - 1);
	if(condition && Snake->line < LINES / 2)
	  newPart->line = Snake->line + 1;
	else if(condition)
	  newPart->line = Snake->line - 1;
	else
	  newPart->column = Snake->column - 1;
      }
      else if(LineDirection == 1) {
	condition = Snake->line + 1 == LINES || SpotTaken(Snake->line + 1, Snake->column);
	if(condition && Snake->column < COLUMNS / 2)
	  newPart->column = Snake->column + 1;
	else if(condition)
	  newPart->column = Snake->column - 1;
	else
	  newPart->line = Snake->line + 1;
      }
      else if(ColDirection == 1) {
	condition = Snake->column + 1 == COLUMNS || SpotTaken(Snake->line, Snake->column + 1);
	if(condition && Snake->line < LINES / 2)
	  newPart->line = Snake->line + 1;
	else if(condition)
	  newPart->line = Snake->line - 1;
	else
	  newPart->column = Snake->column + 1;
      }
      LineDirection = newPart->line - Snake->line;
      ColDirection = newPart->column - Snake->column;
      newPart->next = NULL;
      Snake->next = newPart;
      Snake = Snake->next;
      printf("\033[%d;%dH%s", Snake->line, Snake->column, TailChar);
    }
    */
    
    while(SpotTaken(APPLE[0], APPLE[1])) {
      APPLE[0] = randIntInRange(2, LINES);
      APPLE[1] = randIntInRange(2, COLUMNS);
    }
    printf("\033[%d;%dH%s", APPLE[0], APPLE[1], AppleChar);

    SCORE++;
    LENGTH++;
    STEPTIME -= STEPTIME > MINSTEPTIME ? DELTASTEPTIME : 0;
    printf("\033[0;0HScore: %d", SCORE);
  }

  Snake = SnakeHead;
  printf("\033[%d;%dH\n", 0, COLUMNS);
}

// Directional movement.
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

// Auto-moves the snake forward in the current direction while running in a separate thread.
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

// Main loop of the program, which initializes the program and then is responsible for registering keypresses.
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
  
  Snake->line = randIntInRange(2, LINES);
  Snake->column = randIntInRange(2 + LENGTH, COLUMNS - COLCOMPENSATION);
  Snake->direction = RIGHT;
  Snake->next = NULL;
  SnakeHead = Snake;
  for(int i = 0;i < LENGTH;++i) {
    snake newPart = malloc(sizeof(struct SNAKE));
    newPart->line = Snake->line;
    newPart->column = Snake->column - 1;
    printf("\033[%d;%dH%s", newPart->line, newPart->column, TailChar);
    newPart->next = NULL;
    Snake->next = newPart;
    Snake = Snake->next;
  }
  Snake = SnakeHead;

  do {
    APPLE[0] = randIntInRange(2, LINES);
    APPLE[1] = randIntInRange(2, COLUMNS);
  } while(SpotTaken(APPLE[0], APPLE[1]));
  
  printf("\033[0;0HScore: %d---High Score: %d\033[%d;%dH%s\033[%d;%dH%s\033[0;%dH\n", SCORE, HIGHSCORE, APPLE[0], APPLE[1], AppleChar, Snake->line, Snake->column, HeadChar, COLUMNS);

  usleep(STARTDELAY);
  
  thread = malloc(sizeof(pthread_t));
  pthread_create(thread, NULL, moveForward, NULL);

  for(;;) {
    int c = getchar_unlocked();
    switch(c) {
    case 'w':
      if(Snake->direction != UP && !(Snake->direction == DOWN && LENGTH > 0))
	moveUp();
      break;
    case 'd':
      if(Snake->direction != RIGHT && !(Snake->direction == LEFT && LENGTH > 0))
	moveRight();
      break;
    case 's':
      if(Snake->direction != DOWN && !(Snake->direction == UP && LENGTH > 0))
	moveDown();
      break;
    case 'a':
      if(Snake->direction != LEFT && !(Snake->direction == RIGHT && LENGTH > 0))
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
