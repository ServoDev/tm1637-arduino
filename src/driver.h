// Low level/driver functions
#pragma once

#include <Arduino.h>

// ---- I2C
void Start(); 
void Stop();
void Ack(); // acknowledgement
void SetClock(int val);

// sends 8 bits of data
void Execute(uint8_t data);
// ---- tm1638 operations
void Setup();
void Write(uint8_t data[4], uint8_t has_colon);
void ResetAddr();
void SetBrightness(uint8_t val);
void SetDisplay(uint8_t isOn);


// TODO SET THESE USING CODE BY USER
const int clock_pin = 13;
const int data_pin = 8;
const int clock_period = 5;  // micro seconds

