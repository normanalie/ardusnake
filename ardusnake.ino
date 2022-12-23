#include "LedControl.h"
#include "snake.h"

//Display snake OK
//Move snake forward OK
//Collide wall OK
//Direction OK
//Grow <--
//Collide self
//Generate apple
//Eat apple

#define TPS 1
#define FPS 2*TPS

#define MATRIX_DIN 2
#define MATRIX_CLK 3
#define MATRIX_CS 4

#define UP 11
#define DOWN 9
#define LEFT 10
#define RIGHT 8

LedControl lc = LedControl(MATRIX_DIN, MATRIX_CLK, MATRIX_CS, 1); 
Snake snake;
unsigned long prev_frame = millis();
unsigned long prev_tick = millis();

void test_pattern();
int pressed(); // Return the pressed key or -1
int init_game(); // Called at the end of setup
int update_game();  // Called every TPS
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
  switch(pressed()){
    case UP:
      snake.dir = D_UP;
      break;
    case DOWN:
      snake.dir = D_DOWN;
      break;
    case RIGHT:
      snake.dir = D_RIGHT;
      break;
    case LEFT:
      snake.dir = D_LEFT;
      break;
  }  

  if(millis() - prev_frame >= 1000/FPS){
    update_screen();
    prev_frame = millis();
  }
  
  if(millis() - prev_tick >= 1000/TPS){
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


int pressed(){
  if(!digitalRead(UP)){
    return UP;
  }
  if(!digitalRead(DOWN)){
    return DOWN;
  }
  if(!digitalRead(LEFT)){
    return LEFT;
  }
  if(!digitalRead(RIGHT)){
    return RIGHT;
  }
  return -1;
}


int init_game(){
  test_pattern();
  delay(1000);

  snake_init(&snake, 4, 3);

  prev_frame = millis();
  prev_tick = millis();

  return 0;
}


int update_game(){
  switch(snake.dir){
    case D_RIGHT:
      snake.x++;
      break;
    case D_LEFT:
      snake.x--;
      break;
    case D_UP:
      snake.y++;
      break;
    case D_DOWN:
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
  init_game();
  return 0;
}
