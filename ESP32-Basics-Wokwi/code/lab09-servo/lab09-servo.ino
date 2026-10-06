// Lab 09 - Servo motor
// Servo: signal (orange) -> GPIO 26, V+ (red) -> 5V, GND (brown) -> GND
// Library: ESP32Servo (add it in Wokwi's Library Manager)

#include <ESP32Servo.h>

const int SERVO_PIN = 26;
Servo myServo;

void setup() {
  myServo.attach(SERVO_PIN);   // connect the Servo object to the pin
}

void loop() {
  myServo.write(0);            // 0 degrees   (one end)
  delay(1000);
  myServo.write(90);           // 90 degrees  (middle)
  delay(1000);
  myServo.write(180);          // 180 degrees (other end)
  delay(1000);

  // slow sweep back from 180 to 0
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
