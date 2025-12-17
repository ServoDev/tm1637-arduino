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

    void write(int a, int b, int c, int d) {
      ResetAddr();

      uint8_t arr[4] = {a, b, c, d};

      Write(arr, 0);
    }

    // turns display on/off
    void activate() { SetDisplay(1); };
    void deactivate() { SetDisplay(0); };

    void setBrightness(uint8_t val);

    void startStopwatch() {
      cnt = 0;
      displayTime(cnt);
      active = stopwatch;
      time = millis();
      isPaused = 0;
    }

    void startTimer(int startTime) {
      cnt = startTime;
      displayTime(cnt);
      active = timer;
      time = millis();
      isPaused = 0;
    }


    void pauseStopwatch() {
      isPaused = 1;
    }

    void playStopwatch() {
      isPaused = 0;
      time = millis();
    }

    // TODO DEBUG
    int getCnt() { return cnt; }


  private:
    const int stopwatch = 1;
    const int timer = 2;
    int active;
    bool isPaused;
    unsigned long time;
    unsigned int cnt; // used for stopwatch and timers

    void displayTime(unsigned int cnt);
};

void Display::step() {
  if (!active || isPaused) return;

  if (active == stopwatch) {
    // Serial.println(1);
    // ensure 1 second has passed
    if ((millis() - time) < 1000) { return; }
    cnt++;

    // reset time
    time = millis();


    // display the stopwatch
    displayTime(cnt);

    // stop after 60m
    if (cnt >= 3600) {
      pauseStopwatch();
      return;
    }

  }

  if (active == timer) {
    // ensure 1 second has passed
    if ((millis() - time) < 1000) { return; }
    cnt--;

    // reset time
    time = millis();


    // display the stopwatch
    displayTime(cnt);

    // stop upon hitting 0
    if (cnt == 0) {
      pauseStopwatch(); // not the best name 
      return;
    }
    
  }
} 

// cnt represents how many seconds away from 0
void Display::displayTime(unsigned int cnt) {
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
  // uint8_t debug = seconds / 10;
  // Serial.println(debug);
}

// set the brightness 0 to 7 inclusive
void Display::setBrightness(uint8_t val) {
  // check for invalid input
  if (val > 7) return; // TODO error handle

  SetBrightness(val);
}



Display display;  // decplare display globally
void setup() {
  Serial.begin(9600); 
  display.activate();
  display.write(1, 3, 3, 7);
  display.startStopwatch();
  // display.startStopwatch();
}

int i=0;
void loop() {
  display.step();
  display.setBrightness(i);
  delay(50);
  i++;
  if (i>7) i=0;
}

