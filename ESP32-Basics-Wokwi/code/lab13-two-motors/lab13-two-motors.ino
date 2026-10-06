// Lab 13 - Two motors / robot drive (needs ESP32 Arduino core 3.x)
// Left motor  (OUT1/OUT2): ENA = 32, IN1 = 33, IN2 = 25
// Right motor (OUT3/OUT4): ENB = 14, IN3 = 26, IN4 = 27

const int ENA = 32, IN1 = 33, IN2 = 25;   // left motor
const int ENB = 14, IN3 = 26, IN4 = 27;   // right motor

const int PWM_FREQ = 1000;
const int PWM_RES = 8;

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);
}

// Each side: direction (+1 forward, -1 backward, 0 stop) and speed 0-255
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

void forward(int s)   { setLeft(+1, s); setRight(+1, s); }
void backward(int s)  { setLeft(-1, s); setRight(-1, s); }
void turnLeft(int s)  { setLeft(0, 0);  setRight(+1, s); }   // only right wheel drives
void turnRight(int s) { setLeft(+1, s); setRight(0, 0);  }   // only left wheel drives
void spinLeft(int s)  { setLeft(-1, s); setRight(+1, s); }   // wheels in opposite directions
void stopAll()        { setLeft(0, 0);  setRight(0, 0);  }

void loop() {
  forward(200);   delay(2000);
  stopAll();      delay(500);
  turnLeft(200);  delay(1000);
  turnRight(200); delay(1000);
  backward(200);  delay(2000);
  spinLeft(200);  delay(1000);
  stopAll();      delay(2000);
}
