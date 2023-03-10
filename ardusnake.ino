#include "LedControl.h"
#include "snake.h"

//Display snake OK
//Move snake forward OK
//Collide wall OK
//Direction OK
//Grow OK
//Collide self OK
//Generate apple OK
//Eat apple OK
//Fix illegals move OK
//Fix bad growing when changing direction OK
//Fix RNG to be more random OK
//Fix Apple generation OK

#define TPS 2
#define FPS 10

#define MATRIX_DIN 4
#define MATRIX_CLK 2
#define MATRIX_CS 7

#define UP 11
#define DOWN 10
#define LEFT 12
#define RIGHT 9

LedControl lc = LedControl(MATRIX_DIN, MATRIX_CLK, MATRIX_CS, 1); 
Snake snake;
Apple apple;

void init_rng();
void test_pattern();
int pressed(); // Return the pressed key or -1
int init_game(); // Called at the end of setup
int update_game();  // Called every tick
int update_screen(); // Called every frame
int end_game(); // Called at the end of the game

unsigned long prev_frame = millis();
unsigned long prev_tick = millis();

void setup() {
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  init_rng();

  lc.clearDisplay(0);
  lc.shutdown(0, false);
  lc.setIntensity(0, 3);
  //test_pattern(); 
  init_game();
}

void loop() {
  switch(pressed()){
    case UP:
      snake.tail[0].dir = (snake.tail[0].dir != D_DOWN) ? D_UP : D_DOWN;
      break;
    case DOWN:
      snake.tail[0].dir = (snake.tail[0].dir != D_UP) ? D_DOWN : D_UP;
      break;
    case RIGHT:
      snake.tail[0].dir = (snake.tail[0].dir != D_LEFT) ? D_RIGHT : D_LEFT;
      break;
    case LEFT:
      snake.tail[0].dir = (snake.tail[0].dir != D_RIGHT) ? D_LEFT : D_RIGHT;
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


void init_rng(){
  randomSeed(analogRead(A7)+analogRead(A1));
  return;
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

  apple.x = -1;
  apple.y = -1;
  int ret = apple_generate(&snake, &apple);
  if(ret == 2){  // Too much trial to find a free spot
    init_rng();
    if(apple_generate(&snake, &apple) != 0){ // Try one more time with a different rng seed
      end_game();
    }
  }else if(ret != 0){
    end_game();
  }

  prev_frame = millis();
  prev_tick = millis();

  return 0;
}


int update_game(){
  if(snake.tail[0].x == apple.x && snake.tail[0].y == apple.y){ //Eat apple
    if(snake_grow(&snake) != 0) end_game(); // Grow

    int ret = apple_generate(&snake, &apple); // New apple
    if(ret == 2){  // Too much trial to find a free spot
      init_rng();
      if(apple_generate(&snake, &apple) != 0){ // Try one more time with a different rng seed
        end_game();
      }
    }else if(ret != 0){
      end_game();
    }
  }else{ // Just update
    if(snake_update(&snake, 7, 7) != 0) end_game();
  }
}

int update_screen(){
  lc.clearDisplay(0);
  for(int i = 0; i<=snake.tail_end; i++){
    lc.setLed(0, snake.tail[i].x, snake.tail[i].y, HIGH);
  }
  lc.setLed(0, apple.x, apple.y, HIGH);
  return 0;
}


int end_game(){
  init_game();
  return 0;
}
