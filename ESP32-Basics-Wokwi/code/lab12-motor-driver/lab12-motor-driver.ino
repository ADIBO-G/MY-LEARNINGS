// Lab 12 - DC motor + L298N motor driver (needs ESP32 Arduino core 3.x)
// ENA -> GPIO 32 (PWM speed), IN1 -> GPIO 33, IN2 -> GPIO 25
// L298N: 12V terminal <- battery +, GND terminal <- battery - AND ESP32 GND
// Motor A connects to OUT1 / OUT2. Remove the ENA jumper so PWM can work.

const int ENA = 32;
const int IN1 = 33;
const int IN2 = 25;

const int PWM_FREQ = 1000;
const int PWM_RES = 8;      // duty 0 ... 255

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  ledcAttach(ENA, PWM_FREQ, PWM_RES);
}

void motorForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(ENA, speed);
}

void motorBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(ENA, speed);
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(ENA, 0);
}

void loop() {
  motorForward(255);   // full speed forward
  delay(2000);
  motorStop();
  delay(1000);
  motorBackward(150);  // slower, backward
  delay(2000);
  motorStop();
  delay(1000);
}
