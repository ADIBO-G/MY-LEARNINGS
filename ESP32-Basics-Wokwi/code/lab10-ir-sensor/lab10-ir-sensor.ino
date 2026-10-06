// Lab 10 - IR sensor (digital output)
// IR module: VCC -> 3V3, GND -> GND, OUT -> GPIO 13
// Indicator LED + 220 ohm resistor on GPIO 2.
// NOTE: Wokwi has no built-in IR line sensor. In the simulator, wire a slide
// switch (middle pin -> GPIO 13, side pins -> 3V3 and GND) to play the sensor.

const int IR_PIN = 13;
const int LED_PIN = 2;

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int value = digitalRead(IR_PIN);

  // Most IR line modules give LOW over a light surface (reflection)
  // and HIGH over a black line (no reflection). Check YOUR module!
  if (value == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Sensor = HIGH  -> BLACK line / no reflection");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Sensor = LOW   -> white surface / reflection");
  }
  delay(200);
}
