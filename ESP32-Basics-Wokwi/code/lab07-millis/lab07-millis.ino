// Lab 07 - millis(): two LEDs blinking at different speeds at the same time
// LED1 (GPIO 25) blinks every 500 ms, LED2 (GPIO 26) blinks every 1300 ms.

const int LED1_PIN = 25;
const int LED2_PIN = 26;

const unsigned long INTERVAL1 = 500;    // ms
const unsigned long INTERVAL2 = 1300;   // ms

unsigned long previous1 = 0;   // last time LED1 changed
unsigned long previous2 = 0;   // last time LED2 changed
bool led1State = false;
bool led2State = false;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  unsigned long now = millis();            // milliseconds since the ESP32 started

  if (now - previous1 >= INTERVAL1) {      // has 500 ms passed?
    previous1 = now;
    led1State = !led1State;                // flip ON <-> OFF
    digitalWrite(LED1_PIN, led1State);
  }

  if (now - previous2 >= INTERVAL2) {      // has 1300 ms passed?
    previous2 = now;
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State);
  }

  // loop() keeps running freely - we could read sensors here too!
}
