#ifndef SNAKE_H
#define SNAKE_H
#include "Arduino.h"

#define SNAKE_MAX 64


enum direction {D_RIGHT, D_UP, D_LEFT, D_DOWN};

typedef struct Tail Tail;
struct Tail{
  int x;
  int y;
};

typedef struct{
  int x;
  int y;
  enum direction dir;
  Tail tail[SNAKE_MAX];
  int tail_end;
}Snake;

void snake_init(Snake *snake, int x, int y);

int snake_getX(Snake *snake);

int snake_getY(Snake *snake);

void snake_setX(Snake *snake, int x);

void snake_setY(Snake *snake, int y);

int snake_update(Snake *snake, int max_x, int max_y);

int snake_grow(Snake *snake);

#endif