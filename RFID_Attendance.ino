
// RFID Attendance System with Arduino, RTC, and OLED
// Based on: Random Nerd Tutorials - https://randomnerdtutorials.com/arduino-time-attendance-system-with-rfid/

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_SSD1306.h>

// Pin Configurations
#define SS_PIN 10
#define RST_PIN 9
#define OLED_RESET -1

MFRC522 rfid(SS_PIN, RST_PIN);
RTC_DS3231 rtc;
Adafruit_SSD1306 display(OLED_RESET);

// Replace with your card UIDs
String authorizedUIDs[] = {"A1B2C3D4", "11223344", "DEADBEEF"};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  rtc.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("RFID Attendance");
  display.display();
  delay(2000);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  String uid = getUID();

  display.clearDisplay();
  display.setCursor(0, 0);

  if (isAuthorized(uid)) {
    DateTime now = rtc.now();
    String timestamp = now.timestamp();
    display.println("Access Granted");
    display.println(uid);
    display.println(timestamp);
    Serial.print("UID: ");
    Serial.print(uid);
    Serial.print(" - Time: ");
    Serial.println(timestamp);
  } else {
    display.println("Access Denied");
    display.println(uid);
  }

  display.display();
  delay(2000);
  rfid.PICC_HaltA();
}

// Helper: Get UID as string
String getUID() {
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content;
}

// Helper: Check UID against list
bool isAuthorized(String uid) {
  for (String id : authorizedUIDs) {
    if (uid == id) return true;
  }
  return false;
}
