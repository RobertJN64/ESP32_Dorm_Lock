#include <Arduino.h>
#include <Adafruit_PN532.h>

// TODO - deal with this
#define PN532_IRQ (2)
#define PN532_RESET (3) // Not connected by default on the NFC Shield

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

void fatal_error(const char *err_text) {
  Serial.print(err_text);
  Serial.print(" - restarting");
  delay(5000);
  ESP.restart();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("EPS32 connected!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    fatal_error("Didn't find PN53x board");
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver: ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);
}

void loop() {
  // put your main code here, to run repeatedly:
}
