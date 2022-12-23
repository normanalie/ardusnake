#include "LedControl.h"

//Display snake

#define MATRIX_DIN 3
#define MATRIX_CLK 4
#define MATRIX_CS 5

#define UP 11
#define DOWN 9
#define LEFT 10
#define RIGHT 8

LedControl lc = LedControl(2, 3, 4, 1); 

void test_pattern();

void setup() {
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  lc.clearDisplay(0);
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  test_pattern();
}

void loop() {
  
}


void test_pattern(){
  for(int j = 0; j < 8; j++){
    for(int i = 0; i < 8; i++){
      lc.setLed(0, i, j, HIGH);
      delay(20);
    }
  }
  for(int j = 0; j < 8; j++){
    for(int i = 0; i < 8; i++){
      lc.setLed(0, i, j, LOW);
      delay(20);
    }
  }
  return;
}
