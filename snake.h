#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_MAX 128

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

#endif