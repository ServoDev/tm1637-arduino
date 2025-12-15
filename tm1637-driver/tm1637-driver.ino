// 2025-12-07
// Ryan Blachowicz
// TM1637 basic functionality

#include "driver.h"


class Display {
  public:
    Display() :
    active(0) 
    {
      Setup();
      ResetAddr();
    }


    void step();

    // void Print(int a, int b, int c, int d) {
    //   ResetAddr();
    //
    //   uint8_t arr[4] = {a, b, c, d};
    //
    //   Write(arr, 0);
    // }

    // turns display on/off
    void activate() { SetDisplay(1); };
    void deactivate() { SetDisplay(0); };

    void startStopwatch() {
      active = stopwatch;
      time = millis();
      cnt = 0;
    }


  private:
    const int stopwatch = 1;
    const int timer = 2;
    int active;
    unsigned long time;
    int cnt; // used for stopwatch and timers
};

void Display::step() {
  if (!active) return;

  if (active == stopwatch) {
    // ensure 1 second has passed
    while ((millis() - time) < 1000) {
      // do nothing TODO is this proper
    }
    // reset time
    time = millis();


    // step the stopwatch
    if (cnt >= 3601) return; // stop timer at 60 min
    uint8_t minutes = cnt / 60;
    uint8_t seconds = cnt % 60;

    // what gets displayed
    uint8_t vals[4];

    // set the display vals
    vals[0] = minutes / 10;
    vals[1] = minutes % 10;
    vals[2] = seconds / 10;
    vals[3] = seconds % 10;

    // write to display
    Write(vals, 1);
    uint8_t debug = seconds / 10;
    Serial.println(debug);

    cnt++;
  }

  if (active == timer) {

  }
} 


Display display;  // decplare display globally
void setup() {
  display.activate();
  // display.Print(1, 3, 3, 7);
  display.startStopwatch();
}

void loop() {
  display.step();
}


