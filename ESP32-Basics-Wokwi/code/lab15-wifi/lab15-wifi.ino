// Lab 15 - ESP32 Wi-Fi
// In Wokwi, connect to the free simulated network "Wokwi-GUEST" (no password).
// Status LED + 220 ohm resistor on GPIO 2: ON = connected.

#include <WiFi.h>

const char* WIFI_SSID = "Wokwi-GUEST";   // network name
const char* WIFI_PASSWORD = "";          // no password on Wokwi-GUEST
const int WIFI_CHANNEL = 6;              // Wokwi speeds up connection on channel 6
const int LED_PIN = 2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.print("Connecting to Wi-Fi ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

  while (WiFi.status() != WL_CONNECTED) {   // wait until connected
    delay(250);
    Serial.print(".");
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // blink while connecting
  }

  digitalWrite(LED_PIN, HIGH);              // solid ON = connected
  Serial.println();
  Serial.println("Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {      // lost the connection?
    digitalWrite(LED_PIN, LOW);
    Serial.println("Wi-Fi lost, reconnecting...");
    WiFi.reconnect();
    delay(2000);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }
  delay(1000);
}
