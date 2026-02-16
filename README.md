# TM1637 Arduino Library

![tm1637_2](https://github.com/user-attachments/assets/d4a286fb-fc22-47fc-8e4f-c3f309ee3eda)

The **TM1637** is an IC commonly used in Arduino seven-segment display modules. This project provides a library for these modules that abstracts away the low-level communication protocol and operation codes required to interface with the IC. By adding the library to their sketch, users can easily display numbers, time, and temperature on their displays.

## Features
- Timer
- Stopwatch
- Display numbers and symbols 
- Display temprature easily
- Brightness adjustment

## Setup
``` c
#include <tm1637.h>

Display display(clock_pin, data_pin); // set pins to what is needed

display.activate(); // turn the display on
display.setBrightness(7); // accepts 0 to 7
```

## How to use
#### Directly write to display:
``` c
display.write(1, 6, 3, 7);
display.writeTime(1, 6, 3, 7); // includes the colon
```

#### Stopwatch/timer:
``` c
display.startTimer(60); // 60 second timer
display.startStopwatch();

display.pauseStopwatch(); // pauses timer OR stopwatch
display.playStopwatch();
```

```
// step() must be included in loop function
void loop() {
  display.step();
}

```
#### Temperature
``` c
display.writeTemperature(0); // displays a temperature
display.toggleTemperatureScale(); // defaults to celcius
```

#### Other functions
``` c
display.getCnt() // returns the seconds on timer/stopwatch
display.setClockPeriod(5) // adjust the clock period of the I2C protocol in microseconds
```
