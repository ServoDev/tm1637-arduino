// 2025-12-07
// Ryan Blachowicz
// Put the TM1637 in test mode

const int clock_pin = 13;
const int data_pin = 8;
const int debug_led_pin = 7;  // light up according to clock signal

const int clock_period = 5;  // micro seconds

// indexed to 0-9 followed by A-F followed by degree symbol
const int hex_codes[17] = {
  0x3F, // 0
  0x30, // 1
  0x5B, // 2
  0x79, // 3
  0x74, // 4
  0x6D, // 5
  0x6F, // 6
  0x38, // 7
  0x7F, // 8
  0x7D, // 9

  0x7E, // A
  0x67, // b
  0x0F, // C
  0x73, // d
  0x4F, // E
  0x4E, // F

  0x5C  // degree
};

const int colon_code = 8; // add this to a hex code to include the colon



void setup() {
  // set up pins
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);  // take control
  Serial.begin(9600);

}

void loop() {
  ResetAddr();

  // turn on display
  Start();
  Execute(0x88);
  Ack();
  Stop();

  // write to disp
  Start();
  Execute(0x40);
  Ack();
  //nums
  Execute(hex_codes[8]);
  Ack();
  Execute(hex_codes[9]);
  Ack();
  Execute(hex_codes[16]);
  Ack();
  Execute(hex_codes[15]);
  Ack();
  Stop();



  digitalWrite(data_pin, LOW);
  Halt();
}

void SendChar(uint8_t data)  {

}

// goes back to first digit on display
void ResetAddr() {
  Start();
  Execute(0xC0);
  Ack();
  Stop();
}

// start the i2c transmission
void Start() {
  // Serial.println("Init.");
  SetClock(HIGH);
  digitalWrite(data_pin, HIGH);
  delayMicroseconds(clock_period);
  digitalWrite(data_pin, LOW);
}

// end the i2c transmission
void Stop() {
  SetClock(LOW);
  delayMicroseconds(clock_period);
  digitalWrite(data_pin, LOW);
  delayMicroseconds(clock_period);
  SetClock(HIGH);
  delayMicroseconds(clock_period);
  digitalWrite(data_pin, HIGH);
}

// receive i2c acknowledgement
void Ack() {
  SetClock(LOW);
  // clock is low
  pinMode(data_pin, INPUT);  // release control
  delayMicroseconds(clock_period);

  // set hgigh
  SetClock(HIGH);
  delayMicroseconds(clock_period);

  // receive ACK
  // Serial.println(digitalRead(data_pin));
  if(digitalRead(data_pin) != 0) {
    Serial.println("ACK Not received!");
  }

  // set low
  SetClock(LOW);
  delayMicroseconds(clock_period);

  // REGAIN control
  pinMode(data_pin, OUTPUT);
}

void Execute(uint8_t data) {
  // Serial.println("Executing:");
  // for (int i = 7; i >= 0; i--) {
  for (int i=0; i<8; i++) {
    // set clock to low
    SetClock(LOW);

    // extract first bit 
    uint8_t bit = ((data >> i) & 1) == 1;

    // write first bit
    digitalWrite(data_pin, bit);
    // Serial.print(bit);

    // step clock
    delayMicroseconds(clock_period);
    SetClock(HIGH);
    delayMicroseconds(clock_period);
  }
}

void Halt() {
  while (1) {
    delay(1000);
  }
}

void SetClock(int val) {
  digitalWrite(debug_led_pin, val);
  digitalWrite(clock_pin, val);
}

void Clock_Pulse() {
  // rise clock, data will be read following this
  digitalWrite(debug_led_pin, HIGH);
  digitalWrite(clock_pin, HIGH);
  delayMicroseconds(clock_period);
  // set clock to low
  digitalWrite(debug_led_pin, LOW);
  digitalWrite(clock_pin, LOW);
  delayMicroseconds(clock_period);
}
