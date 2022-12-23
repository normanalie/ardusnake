#ifndef SNAKE_H
#define SNAKE_H

typedef struct Tail Tail;
struct Tail{
  int x;
  int y;
  Tail *next;
};

typedef struct{
  int x;
  int y;
  Tail *next;
}Snake;

#endif