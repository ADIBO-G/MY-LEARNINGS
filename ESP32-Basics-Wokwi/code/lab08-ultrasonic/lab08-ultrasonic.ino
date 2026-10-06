// Lab 08 - Ultrasonic sensor HC-SR04
// VCC -> 5V, GND -> GND, TRIG -> GPIO 18, ECHO -> GPIO 19
// (On real hardware put a voltage divider on ECHO: it outputs 5 V.)

const int TRIG_PIN = 18;
const int ECHO_PIN = 19;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);   // we send the trigger pulse
  pinMode(ECHO_PIN, INPUT);    // we listen for the echo
}

void loop() {
  // 1. send a clean 10 microsecond pulse on TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2. measure how long ECHO stays HIGH (microseconds)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);   // give up after 30 ms

  // 3. convert time to distance
  if (duration == 0) {
    Serial.println("No echo (too far or nothing in front)");
  } else {
    float distance = duration * 0.0343 / 2;         // centimetres
    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.println(" cm");

    if (distance < 20) {
      Serial.println("  -> OBSTACLE!");
    }
  }
  delay(300);
}
