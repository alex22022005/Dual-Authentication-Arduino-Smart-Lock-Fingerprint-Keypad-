#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Keypad.h>

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {4, 5, 6, 8};   // Row pins
byte colPins[COLS] = {9, 10, 11};   // Column pins
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
SoftwareSerial mySerial(2, 3);  // RX = D2, TX = D3
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Servo doorServo;
const int servoPin = 12;
const int solenoidPin = 7;
const String correctPassword = "2356";  
String enteredPassword = "";
bool enteringPassword = false;
void setup() {
  Serial.begin(9600);
  mySerial.begin(57600); 
  finger.begin(57600);   

  if (finger.verifyPassword()) {
    Serial.println("✅ Fingerprint sensor detected!");
  } else {
    Serial.println("❌ Fingerprint sensor not found!");
    while (true); 
  }

  doorServo.attach(servoPin);
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, HIGH); 
}

void loop() {
  Serial.println("🔄 Place Finger or Press # to Enter Password...");

  bool unlocked = false; 

  while (!unlocked) { 
    if (!enteringPassword && checkFingerprint()) {
      openDoor();
      unlocked = true;
    }

    char key = keypad.getKey();
    if (key) {
      Serial.print(key);

      if (key == '#') { 
        if (!enteringPassword) {
          enteringPassword = true;
          enteredPassword = "";
          Serial.println("\n🔢 Enter Password:");
        } else {
          if (enteredPassword == correctPassword) {
            Serial.println("\n✅ Correct password! Door opening...");
            openDoor();
            unlocked = true;
          } else {
            Serial.println("\n❌ Incorrect password! Try again.");
          }
          enteredPassword = "";
          enteringPassword = false;
        }
      } 
      else if (key == '*') { 
        enteredPassword = "";
        Serial.println("\n🔄 Password cleared.");
      } 
      else if (enteringPassword) { 
        enteredPassword += key;
      }
    }
  }
}

// Check fingerprint
bool checkFingerprint() {
  finger.getImage();
  if (finger.image2Tz(1) != FINGERPRINT_OK) return false;
  if (finger.fingerFastSearch() != FINGERPRINT_OK) return false;

  Serial.println("✅ Fingerprint matched!");
  return true;
}

// Open the door
void openDoor() {
  Serial.println("🔓 Door Unlocked!");
  digitalWrite(solenoidPin, LOW); 
  delay(1000);
  doorServo.write(60); 
  delay(8000); 

  Serial.println("🔒 Door Closing...");
  doorServo.write(0);
  delay(1500);
  digitalWrite(solenoidPin, HIGH);
  Serial.println("🔒 Door Locked!");
}