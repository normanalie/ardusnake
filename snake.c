#include "snake.h"

void snake_init(Snake *snake, int x, int y){
  snake->tail[0].x = x;
  snake->tail[0].y = y;
  snake->dir = RIGHT;
  snake->tail_end = 0; // Head only 
  return;
}

int snake_incrX(Snake *snake){
  snake->tail[0].x++;
  if(snake->tail[0].x > )
  return;
}

int snake_decrX(Snake *snake){
  return snake->tail[0].x;
}