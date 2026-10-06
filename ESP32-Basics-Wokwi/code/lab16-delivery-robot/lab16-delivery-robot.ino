// Lab 16 - FINAL PROJECT: Line-following delivery robot
// Needs ESP32 Arduino core 3.x and the ESP32Servo library.
//
// IR left -> 22, IR right -> 19          (HIGH = sees the black line)
// HC-SR04 TRIG -> 5, ECHO -> 18
// Servo (delivery gate) -> 17
// L298N left motor : ENA 32, IN1 33, IN2 25
// L298N right motor: ENB 14, IN3 26, IN4 27

#include <ESP32Servo.h>

const int IR_LEFT = 22, IR_RIGHT = 19;
const int TRIG_PIN = 5, ECHO_PIN = 18;
const int SERVO_PIN = 17;
const int ENA = 32, IN1 = 33, IN2 = 25;
const int ENB = 14, IN3 = 26, IN4 = 27;

const int SPEED = 170;                 // motor speed 0-255
const int OBSTACLE_CM = 15;            // stop if something is closer than this
const unsigned long CLEAR_TIME = 1000; // path must be clear this long (ms)

enum State { FOLLOW, OBSTACLE, DELIVER, DONE };
State state = FOLLOW;
State lastShown = DONE;                // forces the first status print

Servo gate;
unsigned long clearSince = 0;

// ---------- motors ----------
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
void stopMotors() { setLeft(0, 0); setRight(0, 0); }

// ---------- sensors ----------
float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);   // 30 ms time-out
  if (duration == 0) return 999;                    // nothing heard
  return duration * 0.0343 / 2;
}

// Line following (Lab 14). Returns true when BOTH sensors see black = destination.
bool followLine() {
  bool l = digitalRead(IR_LEFT) == HIGH;
  bool r = digitalRead(IR_RIGHT) == HIGH;
  if (l && r)       { stopMotors(); return true; }
  else if (l)       { setLeft(0, 0);       setRight(+1, SPEED); }  // steer left
  else if (r)       { setLeft(+1, SPEED);  setRight(0, 0);      }  // steer right
  else              { setLeft(+1, SPEED);  setRight(+1, SPEED); }  // straight
  return false;
}

// ---------- status ----------
// Put OLED code here (Lab 11) if you add a display.
void showStatus() {
  if (state == lastShown) return;      // only print when the state changes
  lastShown = state;
  switch (state) {
    case FOLLOW:   Serial.println("STATUS: following line");        break;
    case OBSTACLE: Serial.println("STATUS: obstacle! waiting");     break;
    case DELIVER:  Serial.println("STATUS: delivering package");    break;
    case DONE:     Serial.println("STATUS: delivery complete");     break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_LEFT, INPUT);  pinMode(IR_RIGHT, INPUT);
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  ledcAttach(ENA, 1000, 8);
  ledcAttach(ENB, 1000, 8);
  gate.attach(SERVO_PIN);
  gate.write(0);                       // gate closed
  stopMotors();
}

void loop() {
  showStatus();
  float distance = readDistanceCm();

  switch (state) {
    case FOLLOW:
      if (distance < OBSTACLE_CM) {            // something in the way
        stopMotors();
        clearSince = 0;
        state = OBSTACLE;
      } else if (followLine()) {               // reached the destination mark
        state = DELIVER;
      }
      break;

    case OBSTACLE:
      stopMotors();
      if (distance >= OBSTACLE_CM) {           // path looks clear...
        if (clearSince == 0) clearSince = millis();
        if (millis() - clearSince >= CLEAR_TIME) state = FOLLOW;   // ...for long enough
      } else {
        clearSince = 0;                        // blocked again - restart the timer
      }
      break;

    case DELIVER:
      stopMotors();
      showStatus();
      gate.write(90);                          // open the gate: package drops
      delay(1500);                             // robot is stopped, so a delay is OK here
      gate.write(0);                           // close the gate
      state = DONE;
      break;

    case DONE:
      stopMotors();                            // reset the ESP32 to run again
      break;
  }
  delay(20);
}
