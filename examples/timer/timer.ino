#include <tm1637.h>

#include <Arduino.h>


Display display;
void setup() {
  display.activate();

  display.write(1, 6, 3, 7);
}

void loop() {

}
