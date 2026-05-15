#include <BluetoothSerial.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

BluetoothSerial SerialBT;
DHT dht(DHTPIN, DHTTYPE);

const unsigned long READ_INTERVAL = 1500;   // 1.5 seconds

bool btStreaming = false;
unsigned long lastRead = 0;
unsigned long readingCount = 0;

void sendToBluetooth(const String &text) {
  if (btStreaming && SerialBT.hasClient()) {
    SerialBT.println(text);
  }
}

void sendToSerial(const String &text) {
  Serial.println(text);
}

void sendBoth(const String &text) {
  sendToSerial(text);
  sendToBluetooth(text);
}

void printReadings(float temperature, float humidity, float heatIndex) {
  readingCount++;

  String header = "Reading #" + String(readingCount);
  String temp   = "Temperature : " + String(temperature, 1) + " °C";
  String hum    = "Humidity    : " + String(humidity, 1) + " %";
  String hi     = "Heat Index  : " + String(heatIndex, 1) + " °C";

  sendBoth(header);
  sendBoth(temp);
  sendBoth(hum);
  sendBoth(hi);
  sendBoth("");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();
  SerialBT.begin("ESP32_DHT11");

  Serial.println();
  Serial.println("ESP32 DHT11 Bluetooth Monitor Ready");
  Serial.println("Bluetooth Name: ESP32_DHT11");
  Serial.println("Commands: START / STOP");
  Serial.println();
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim();
    command.toUpperCase();

    if (command == "START") {
      readingCount = 0;          // Restart counting from 1
      btStreaming = true;
      lastRead = 0;              // Force immediate reading

      sendBoth("Bluetooth streaming started.");
      sendBoth("");
    }
    else if (command == "STOP") {
      btStreaming = false;

      Serial.println("Bluetooth streaming stopped.");

      if (SerialBT.hasClient()) {
        SerialBT.println("Bluetooth streaming stopped.");
        SerialBT.println();
      }
    }
  }

  if (millis() - lastRead >= READ_INTERVAL) {
    lastRead = millis();

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      sendBoth("DHT11 read failed.");
      sendBoth("");
      return;
    }

    float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

    if (isnan(heatIndex)) {
      heatIndex = temperature;
    }

    printReadings(temperature, humidity, heatIndex);
  }
}