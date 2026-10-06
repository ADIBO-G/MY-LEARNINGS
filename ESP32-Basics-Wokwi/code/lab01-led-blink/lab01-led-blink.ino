// Lab 01 - LED Blink
// LED + 220 ohm resistor on GPIO 2, other LED leg to GND.

const int LED_PIN = 2;   // the GPIO pin the LED is connected to

void setup() {
  pinMode(LED_PIN, OUTPUT);   // tell the ESP32 this pin sends signals OUT
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // 3.3 V on the pin -> LED ON
  delay(1000);                 // wait 1 second
  digitalWrite(LED_PIN, LOW);  // 0 V on the pin   -> LED OFF
  delay(1000);                 // wait 1 second
}
