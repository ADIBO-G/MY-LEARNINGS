// Lab 04 - Traffic Light
// Red LED = GPIO 25, Yellow LED = GPIO 26, Green LED = GPIO 27
// (each LED has its own 220 ohm resistor, all LED cathodes go to GND)

const int RED_PIN = 25;
const int YELLOW_PIN = 26;
const int GREEN_PIN = 27;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  // RED - stop
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  delay(3000);

  // GREEN - go
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(3000);

  // YELLOW - get ready to stop
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);

  digitalWrite(YELLOW_PIN, LOW);   // then the loop starts again with RED
}
