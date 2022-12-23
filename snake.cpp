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
  //Start from the end of the tail and move each element to the place of the previous
  for(int i = snake->tail_end; i > 0; i--){
    snake->tail[i].x = snake->tail[i-1].x;
    snake->tail[i].y = snake->tail[i-1].y;
  }
  
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


int snake_grow(Snake *snake){
  if(snake->tail_end >= SNAKE_MAX){
    return 1;
  }
  snake->tail_end++;
  int end = snake->tail_end;

  int x = snake->tail[end-1].x;
  int y = snake->tail[end-1].y;
  switch(snake->dir){
    case D_RIGHT:
      x--;
      break;
    case D_LEFT:
      x++;
      break;
    case D_UP:
      y--;
      break;
    case D_DOWN:
      y++;
      break;
  }   
  snake->tail[end].x = x;
  snake->tail[end].y = y;
  return 0;
}