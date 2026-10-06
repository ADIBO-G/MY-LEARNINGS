// Lab 06 - PWM LED dimming (needs ESP32 Arduino core 3.x, which Wokwi uses)
// LED + 220 ohm resistor on GPIO 18.

const int LED_PIN = 18;
const int PWM_FREQ = 5000;       // 5000 flashes per second
const int PWM_RESOLUTION = 8;    // 8 bits -> duty values 0 ... 255

void setup() {
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);  // set up PWM on this pin
}

void loop() {
  // fade IN: dark -> bright
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(LED_PIN, duty);
    delay(8);
  }
  // fade OUT: bright -> dark
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(LED_PIN, duty);
    delay(8);
  }
}
