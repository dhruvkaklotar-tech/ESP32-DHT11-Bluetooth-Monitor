# 📡 ESP32 & DHT11 Bluetooth Environment Monitor

<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/8/87/Arduino_Logo.svg" alt="Arduino IDE" width="70"/>
  &nbsp;&nbsp;&nbsp;&nbsp;
  <img src="https://upload.wikimedia.org/wikipedia/commons/d/da/Bluetooth_Symbol_With_Background.svg" alt="Bluetooth" width="70"/>
</div>

<br>

A robust IoT project utilizing the **ESP32 DevKit V1** and a **DHT11 Sensor** to continuously monitor environmental conditions. The system calculates temperature, humidity, and heat index, updating the data every 1.5 seconds. Readings are transmitted wirelessly via Bluetooth Classic to an Android smartphone and can also be monitored locally via PC.

## ✨ Project Features
- **Real-Time Monitoring:** Captures Temperature (°C/°F), Humidity (%), and calculates the Heat Index.
- **Reading Counter:** Includes a built-in cycle counter to track exactly how many successful readings have been captured since the device powered on.
- **Fast Refresh Rate:** System updates and transmits data every 1.5 seconds.
- **Dual Display Modes:** 
  - Wirelessly via Android smartphone.
  - Locally via USB using the Arduino IDE Serial Monitor.

---

## ⚠️ Important Precautions & Hardware Safety
Please read these carefully before building the project to avoid damaging your components:
1. **Voltage Warning:** The ESP32 is a **3.3V logic device**. Do NOT connect 5V directly to the ESP32 GPIO pins, or it will fry the board. Power the DHT11 using the `3V3` pin, not `VIN` or `5V`.
2. **Wiring Direction:** Ensure the DHT11 is wired correctly. Reversing the VCC and GND pins will cause the sensor to overheat instantly and permanently break.
3. **Power Supply:** If your ESP32 keeps restarting or dropping the Bluetooth connection, it means your USB cable or PC port is not providing enough power. Try a different cable or a powered USB hub.

---

## 🔌 Complete Circuit Connections

Disconnect the ESP32 from your PC before wiring. 

| DHT11 Pin | ESP32 DevKit V1 Pin | Description |
| :--- | :--- | :--- |
| **VCC (+)** | `3V3` | Provides 3.3V power to the sensor. |
| **DATA (Out)**| `GPIO 4` *(Update if different)* | Sends environmental data to the board. |
| **GND (-)** | `GND` | Ground connection. |

*(Note: If you are using a bare DHT11 sensor without a breakout board, you will need a 10kΩ pull-up resistor between VCC and DATA).*

---

## 💻 PC Setup & Instructions

To flash this code to your ESP32, follow these steps on your computer:

1. **Install Arduino IDE:** Download and install the latest [Arduino IDE](https://www.arduino.cc/en/software).
2. **Add ESP32 Board Support:**
   - Go to `File` > `Preferences`.
   - Paste `https://dl.espressif.com/dl/package_esp32_index.json` into the *Additional Boards Manager URLs* field.
   - Go to `Tools` > `Board` > `Boards Manager`, search for **esp32** by Espressif Systems, and install it.
3. **Install Required Libraries:**
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.
   - Search for **"DHT sensor library"** by Adafruit and install it.
   - Search for **"Adafruit Unified Sensor"** and install it.
4. **Upload the Code:**
   - Connect your ESP32 to your PC via a data-capable Micro-USB/USB-C cable.
   - Open `ESP32_DHT11_Monitor.ino`.
   - Go to `Tools` > `Board` and select **DOIT ESP32 DEVKIT V1**.
   - Go to `Tools` > `Port` and select your COM port.
   - Click the **Upload** button (Right Arrow icon). *(Note: On some ESP32 boards, you must hold the `BOOT` button on the board when you see "Connecting..." at the bottom of the screen).*

---

## 📱 Mobile App Setup (Bluetooth Terminal)

To view the readings wirelessly, this project uses the **Serial Bluetooth Terminal** app.

**App Description:** Serial Bluetooth Terminal by Kai Morich is a highly reliable, line-oriented terminal/console app for microcontrollers. It supports Bluetooth Classic and BLE, making it the perfect tool for monitoring serial outputs directly on your phone.

1. Download the app from the Google Play Store: [Serial Bluetooth Terminal by Kai Morich](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal).
2. Power on your ESP32.
3. Go to your phone's native **Bluetooth Settings** and pair with the device (it will be named `ESP32_DHT11` or whatever you named it in the code).
4. Open the Serial Bluetooth Terminal app.
5. Tap the **Menu icon (≡)** in the top left > **Devices** > **Bluetooth Classic**.
6. Select your ESP32. 
7. Tap the **Connect icon** (looks like two plugs connecting) at the top of the screen. You will now see your readings and the reading counter updating every 1.5 seconds!
