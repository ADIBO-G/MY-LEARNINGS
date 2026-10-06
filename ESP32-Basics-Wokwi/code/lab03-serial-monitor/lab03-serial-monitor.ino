// Lab 03 - Serial Monitor
// Same circuit as Lab 02 (button on GPIO 4, LED on GPIO 2),
// but now the ESP32 TELLS us what it is thinking.

const int BUTTON_PIN = 4;
const int LED_PIN = 2;

int pressCount = 0;          // how many times the button was pressed
int lastState = HIGH;        // previous button reading (HIGH = not pressed)

void setup() {
  Serial.begin(115200);      // start the Serial Monitor at 115200 baud
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("ESP32 is ready!");
}

void loop() {
  int state = digitalRead(BUTTON_PIN);

  if (state == LOW) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // Count only the moment the button goes from "not pressed" to "pressed"
  if (state == LOW && lastState == HIGH) {
    pressCount++;
    Serial.print("Button pressed! Count = ");
    Serial.println(pressCount);
  }
  lastState = state;

  delay(20);                 // small pause so we do not flood the monitor
}
