// Low level/driver functions

#ifndef DRIVER_H
#define DRIVER_H
#include <Arduino.h>

void Setup();
void Write(uint8_t data[4], uint8_t has_colon);
void ResetAddr();
void Start();
void Stop();
void Ack();
void Execute(uint8_t data);
void SetClock(int val);
void SetBrightness(uint8_t val);

void SetDisplay(uint8_t isOn);


// TODO SET THESE USING CODE BY USER
const int clock_pin = 13;
const int data_pin = 8;
const int clock_period = 5;  // micro seconds


#endif
