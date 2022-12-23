#include "LedControl.h"
#include "snake.h"

//Display snake OK
//Move snake forward OK
//Collide wall OK
//Direction
//Grow
//Collide self
//Generate apple
//Eat apple

#define TICK 1
#define FPS 30

#define MATRIX_DIN 3
#define MATRIX_CLK 4
#define MATRIX_CS 5

#define UP 11
#define DOWN 9
#define LEFT 10
#define RIGHT 8

LedControl lc = LedControl(2, 3, 4, 1); 
Snake snake;
unsigned long prev_frame = millis();
unsigned long prev_tick = millis();

void test_pattern();
int init_game(); // Called at the end of setup
int update_game();  // Called every tick
int update_screen(); // Called every frame
int end_game(); // Called at the end of the game

void setup() {
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  lc.clearDisplay(0);
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  //test_pattern();
  init_game();
}

void loop() {
  if(millis() - prev_frame >= 1000/FPS){
    update_screen();
    prev_frame = millis();
  }
  
  if(millis() - prev_tick >= 1000/TICK){
    update_game();
    prev_tick = millis();
  }
}


void test_pattern(){
  for(int j = 0; j < 8; j++){
    for(int i = 0; i < 8; i++){
      lc.setLed(0, i, j, HIGH);
      delay(15);
    }
  }
  for(int j = 0; j < 8; j++){
    for(int i = 0; i < 8; i++){
      lc.setLed(0, i, j, LOW);
      delay(15);
    }
  }
  return;
}


int init_game(){
  test_pattern();
  delay(1000);

  snake.x = 4;
  snake.y = 3;
  snake.dir = RIGHT;
  snake.next = NULL;

  prev_frame = millis();
  prev_tick = millis();

  return 0;
}


int update_game(){
  switch(snake.dir){
    case RIGHT:
      snake.x++;
      break;
    case LEFT:
      snake.x--;
      break;
    case UP:
      snake.y++;
      break;
    case DOWN:
      snake.y--;
      break;
  }

  if(snake.x > 7){
    snake.x = 7;
    end_game();
  }else if(snake.x < 0){
    snake.x = 0;
    end_game();    
  }
  
  if(snake.y > 7){
    snake.y = 7;
    end_game();
  }else if(snake.y < 0){
    snake.y = 0;
    end_game();
  }
  return 0;
}

int update_screen(){
  lc.clearDisplay(0);
  lc.setLed(0, snake.x, snake.y, HIGH);
  return 0;
}


int end_game(){
  delay(200);
  init_game();
  return 0;
}
