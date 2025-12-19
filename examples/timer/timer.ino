#include <Arduino.h>
#include <tm1637.h>

// change these as needed
const int clock_pin = 13;
const int data_pin = 8;

Display display(clock_pin, data_pin);
void setup() {
  // turn on display
  display.activate();

  // 997 seconds on the timer 
  display.startTimer(997);

}

void loop() {
  display.step();

  // do other stuff here

}
