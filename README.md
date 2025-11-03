# 🔒 Dual-Authentication Arduino Smart Lock (Fingerprint & Keypad)

This project is an Arduino-based smart lock system that provides two methods of authentication: a fingerprint sensor and a keypad for a PIN. It's designed to control both a servo motor (for a latch) and a solenoid lock (for a deadbolt).



## 🌟 Features

* **Dual Authentication:** Unlock with either a registered fingerprint or a secret PIN.
* **High Security:** Manages both a solenoid lock and a servo motor for a two-stage locking mechanism.
* **User Feedback:** Provides clear status updates via the Serial Monitor (e.g., "Fingerprint sensor detected!", "✅ Correct password!", "🔒 Door Locked!").
* **Simple Keypad Controls:**
    * `#`: Press to start password entry.
    * `[PIN]`: Enter your secret PIN.
    * `#`: Press again to confirm the PIN.
    * `*`: Press at any time to clear the current password entry and restart.

---

## 🛠️ Hardware Required

* Arduino (e.g., Uno, Nano)
* Adafruit Fingerprint Sensor (e.g., R307, R503)
* 4x3 Matrix Keypad
* Servo Motor (e.g., SG90, MG996R)
* 12V Solenoid Lock
* 5V Relay Module (to safely control the 12V solenoid with the Arduino)
* Breadboard and Jumper Wires
* External 9-12V Power Supply (for the solenoid and servo)

---

## 📚 Libraries Used

* [`Adafruit_Fingerprint.h`](https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library)
* [`SoftwareSerial.h`](https://www.arduino.cc/en/reference/softwareserial) (Comes with the Arduino IDE)
* [`Servo.h`](https://www.arduino.cc/reference/en/libraries/servo/) (Comes with the Arduino IDE)
* [`Keypad.h`](https://github.com/Chris--A/Keypad)

---

## 🔌 Wiring Diagram

Connect the components as defined in the sketch:

| Component | Pin | Arduino Pin |
| :--- | :--- | :--- |
| **Fingerprint Sensor** | RX | Pin 3 (Software TX) |
| | TX | Pin 2 (Software RX) |
| **Keypad** | Row 1-4 | Pins 4, 5, 6, 8 |
| | Col 1-3 | Pins 9, 10, 11 |
| **Servo Motor** | Signal | Pin 12 |
| **Relay Module** | IN | Pin 7 |
| **Solenoid Lock** | + | 12V+ from External PSU |
| | - | Relay 'NO' (Normally Open) |

* Connect the Relay's 'COM' pin to the External PSU's Ground (-).
* Connect the Arduino's GND to the External PSU's Ground (-).
* Power the Servo and Relay VCC pins from the Arduino's 5V pin (or an external 5V supply if the servo draws too much current).

---

## 🚀 How to Use

### 1. Enroll Fingerprints
**This code does not enroll new fingerprints.** You must first use the `enroll` example sketch (which comes with the `Adafruit_Fingerprint` library) to add and store fingerprints in the sensor's memory.

### 2. Upload the Code
Upload the main project sketch to your Arduino board.

### 3. Operation
Open the Serial Monitor (Baud: 9600) to see status messages.

* **To Unlock with Fingerprint:**
    1.  Place a registered finger on the sensor.
    2.  If the finger is recognized, the serial monitor will display "✅ Fingerprint matched!" and the door will unlock.

* **To Unlock with Keypad:**
    1.  Press `#` to begin password entry.
    2.  The serial monitor will display "🔢 Enter Password:".
    3.  Type your 4-digit PIN (the default is `2356`).
    4.  Press `#` again to confirm.
    5.  If correct, the door will unlock. If incorrect, it will ask you to try again.

---

## ⚙️ Configuration

To change the default password, modify this line in the code:

```cpp
const String correctPassword = "2356";
```
## 📄 License
This project is open-source and available under the MIT License.
