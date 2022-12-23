#ifndef SNAKE_H
#define SNAKE_H

enum direction {RIGHT, UP, LEFT, DOWN};

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