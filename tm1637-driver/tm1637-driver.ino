// 2025-12-07
// Ryan Blachowicz
// Put the TM1637 in test mode

const int clock_pin = 13;
const int data_pin = 8;
const int debug_led_pin = 7;  // light up according to clock signal

const int clock_period = 100;  // ms



void setup() {
  // set up pins
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);  // take control
  Serial.begin(9600);

}

void loop() {
  // Set data here


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
  Execute(0x01);
  Ack();
  Execute(0x01);
  Ack();
  Execute(0x01);
  Ack();
  Execute(0x01);
  Ack();
  Stop();



  digitalWrite(data_pin, LOW);
  Halt();
}


// start the i2c transmission
void Start() {
  Serial.println("Init.");
  SetClock(HIGH);
  digitalWrite(data_pin, HIGH);
  delay(1000);
  digitalWrite(data_pin, LOW);
}

// end the i2c transmission
void Stop() {
  SetClock(LOW);
  delay(clock_period / 2);
  digitalWrite(data_pin, LOW);
  delay(clock_period / 2);
  SetClock(HIGH);
  delay(clock_period / 2);
  digitalWrite(data_pin, HIGH);
}

// receive i2c acknowledgement
void Ack() {
  SetClock(LOW);
  // clock is low
  pinMode(data_pin, INPUT);  // release control
  delay(clock_period / 2);

  // set hgigh
  SetClock(HIGH);
  delay(clock_period / 2);

  // receive ACK
  // Serial.println(digitalRead(data_pin));
  if(digitalRead(data_pin) != 0) {
    Serial.println("ACK Not received!");
  }

  // set low
  SetClock(LOW);
  delay(clock_period / 2);

  // REGAIN control
  pinMode(data_pin, OUTPUT);
}

void Execute(uint8_t data) {
  Serial.println("Executing:");
  // for (int i = 7; i >= 0; i--) {
  for (int i=0; i<8; i++) {
    // set clock to low
    SetClock(LOW);

    // extract first bit 
    uint8_t bit = ((data >> i) & 1) == 1;

    // write first bit
    digitalWrite(data_pin, bit);
    Serial.print(bit);

    // step clock
    delay(clock_period / 2);
    SetClock(HIGH);
    delay(clock_period / 2);
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
  delay(clock_period / 2);
  // set clock to low
  digitalWrite(debug_led_pin, LOW);
  digitalWrite(clock_pin, LOW);
  delay(clock_period / 2);
}
