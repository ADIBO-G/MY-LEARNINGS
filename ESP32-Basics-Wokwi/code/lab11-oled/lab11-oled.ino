// Lab 11 - OLED display (SSD1306, 128x64, I2C)
// SDA -> GPIO 21, SCL -> GPIO 22, VCC -> 3V3, GND -> GND
// Libraries: Adafruit SSD1306 + Adafruit GFX Library

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_ADDRESS = 0x3C;     // the I2C "street number" of this display

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int counter = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);              // SDA = 21, SCL = 22

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED not found - check SDA/SCL wires!");
    while (true) { delay(1000); }  // stop here
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Hello, ESP32!");
  display.display();               // nothing appears until display() is called
  delay(1500);
}

void loop() {
  // a made-up "sensor value" that slowly rises and falls (0 - 100)
  int fakeSensor = 50 + 50 * sin(counter / 10.0);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("ESP32 + OLED");
  display.println();
  display.print("Uptime: ");
  display.print(millis() / 1000);
  display.println(" s");
  display.print("Counter: ");
  display.println(counter);
  display.setTextSize(2);
  display.print("S=");
  display.print(fakeSensor);
  display.display();

  counter++;
  delay(200);
}
