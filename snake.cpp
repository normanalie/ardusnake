#include "Arduino.h"
#include "snake.h"

void snake_init(Snake *snake, int x, int y){
  snake->tail[0].x = x;
  snake->tail[0].y = y;
  snake->dir = D_RIGHT;
  snake->tail_end = 0; // Head only 
  return;
}

int snake_getX(Snake *snake){
  return snake->tail[0].x;
}

int snake_getY(Snake *snake){
  return snake->tail[0].y;
}

void snake_setX(Snake *snake, int x){
  snake->tail[0].x = x;
  return;
}

void snake_setY(Snake *snake, int y){
  snake->tail[0].y = y;
  return;
}

int snake_update(Snake *snake, int max_x, int max_y){
  switch(snake->dir){
    case D_RIGHT:
      snake->tail[0].x++;
      break;
    case D_LEFT:
      snake->tail[0].x--;
      break;
    case D_UP:
      snake->tail[0].y++;
      break;
    case D_DOWN:
      snake->tail[0].y--;
      break;
  }

  if(snake->tail[0].x > max_x){
    snake->tail[0].x = max_x;
    return 1;
  }else if(snake->tail[0].x < 0){
    snake->tail[0].x = 0;
    return 1;   
  }
  
  if(snake->tail[0].y > max_y){
    snake->tail[0].y = max_y;
    return 1;
  }else if(snake->tail[0].y < 0){
    snake->tail[0].y = 0;
    return 1;
  }
  return 0;
}