#ifndef SNAKE_H
#define SNAKE_H

enum direction {D_RIGHT, D_UP, D_LEFT, D_DOWN};

typedef struct Tail Tail;
struct Tail{
  int x;
  int y;
  Tail *next;
};

typedef struct{
  int x;
  int y;
  enum direction dir;
  Tail *next;
}Snake;

#endif