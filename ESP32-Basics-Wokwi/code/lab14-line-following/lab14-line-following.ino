// Lab 14 - Line following (2 IR sensors + L298N + 2 motors)
// Needs ESP32 Arduino core 3.x.
// IR left -> GPIO 22, IR right -> GPIO 19   (HIGH = sees the black line)
// Left motor : ENA 32, IN1 33, IN2 25   Right motor: ENB 14, IN3 26, IN4 27
// Wokwi has no IR line sensor: use two slide switches to play the sensors.

const int IR_LEFT = 22;
const int IR_RIGHT = 19;

const int ENA = 32, IN1 = 33, IN2 = 25;
const int ENB = 14, IN3 = 26, IN4 = 27;

const int BASE_SPEED = 170;   // 0-255
const int TURN_SPEED = 170;

void setLeft(int dir, int speed) {
  digitalWrite(IN1, dir > 0);
  digitalWrite(IN2, dir < 0);
  ledcWrite(ENA, dir == 0 ? 0 : speed);
}
void setRight(int dir, int speed) {
  digitalWrite(IN3, dir > 0);
  digitalWrite(IN4, dir < 0);
  ledcWrite(ENB, dir == 0 ? 0 : speed);
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  ledcAttach(ENA, 1000, 8);
  ledcAttach(ENB, 1000, 8);
}

void loop() {
  bool leftOnLine = digitalRead(IR_LEFT) == HIGH;
  bool rightOnLine = digitalRead(IR_RIGHT) == HIGH;

  if (!leftOnLine && !rightOnLine) {          // line is between the sensors
    setLeft(+1, BASE_SPEED); setRight(+1, BASE_SPEED);
    Serial.println("FORWARD");
  } else if (leftOnLine && !rightOnLine) {    // line drifted to the left
    setLeft(0, 0);           setRight(+1, TURN_SPEED);
    Serial.println("TURN LEFT");
  } else if (!leftOnLine && rightOnLine) {    // line drifted to the right
    setLeft(+1, TURN_SPEED); setRight(0, 0);
    Serial.println("TURN RIGHT");
  } else {                                    // both on black: junction / finish
    setLeft(0, 0);           setRight(0, 0);
    Serial.println("STOP");
  }
  delay(20);
}
