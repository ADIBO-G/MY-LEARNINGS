// Lab 02 - Button + LED
// Button between GPIO 4 and GND (uses the internal pull-up resistor).
// LED + 220 ohm resistor on GPIO 2.

const int BUTTON_PIN = 4;
const int LED_PIN = 2;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // pin reads HIGH until the button pulls it to GND
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);  // read the button: HIGH or LOW

  if (buttonState == LOW) {          // LOW means the button is pressed
    digitalWrite(LED_PIN, HIGH);     // LED ON
  } else {
    digitalWrite(LED_PIN, LOW);      // LED OFF
  }
}
