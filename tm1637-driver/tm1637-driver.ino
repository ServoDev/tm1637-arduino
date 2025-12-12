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


    void Step() {
      if (!active) return;
    } 

    void Print(int a, int b, int c, int d) {
      ResetAddr();

      uint8_t arr[4] = {a, b, c, d};

      Write(arr, 0);
    }

    // turns display on/off
    void Activate() { SetDisplay(1); };
    void Deactivate() { SetDisplay(0); };


  private:
    const int stopwatch = 1;
    const int timer = 2;
    int active;
};


void setup() {

}

void loop() {
  
  Display display; 
  display.Activate();
  // display.Print(1, 3, 3, 7);
  StartStopwatch();
  

  Halt();
}


void StartStopwatch() {
  // what gets displayed
  uint8_t vals[4] = {2, 1, 0, 1};

  // seconds passed
  int cnt = 0;
  while (1) {
    if (cnt >= 3601) return; // stop timer at 60 min
    uint8_t minutes = cnt / 60;
    uint8_t seconds = cnt % 60;

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
    delay(10);
  }
}
