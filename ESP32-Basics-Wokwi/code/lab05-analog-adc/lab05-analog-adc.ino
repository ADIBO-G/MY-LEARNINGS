// Lab 05 - Analog input (ADC) with a potentiometer
// Pot: VCC -> 3V3, GND -> GND, SIG (middle pin) -> GPIO 34

const int POT_PIN = 34;   // GPIO 34 is an input-only ADC pin

void setup() {
  Serial.begin(115200);
}

void loop() {
  int raw = analogRead(POT_PIN);                 // 0 ... 4095
  float volts = raw * 3.3 / 4095.0;              // convert to volts
  int percent = map(raw, 0, 4095, 0, 100);       // convert to 0-100 %

  Serial.print("ADC = ");
  Serial.print(raw);
  Serial.print("   Voltage = ");
  Serial.print(volts, 2);
  Serial.print(" V   Percent = ");
  Serial.print(percent);
  Serial.println(" %");

  delay(200);
}
