#include <Arduino.h>
#include <tm1637.h>

// change these as needed
const int clock_pin = 13;
const int data_pin = 8;


Display display(clock_pin, data_pin);
void setup() {
  // turn on display
  display.activate();

  // the library defaults to celsius
  // switch to fahrenheit
  display.toggleTemperatureScale();
}

// print a "temp" in fahrenheit then celsius then increment that temp and repeat
int i = 32; // in terms of fahrenheit
void loop() {
  // display fahrenheit
  display.writeTemperature(i);
  delay(1000); // delay 1 second

  // switch to celsius
  display.toggleTemperatureScale();

  // display celsius
  display.writeTemperature(fahrenheitToCelsius(i));
  delay(1000); // delay 1 second

  // switch to fahrenheit
  display.toggleTemperatureScale();

  i++;
  if (i > 99) i=32; // wrap around 
}

int fahrenheitToCelsius(int f) {
    return (f - 32) * 5 / 9;
}
