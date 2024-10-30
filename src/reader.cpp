#include <SPI.h>
#include <Adafruit_PN532.h>

Adafruit_PN532 nfc(22);

void nfc_init() {
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Did not find the shield - locking up");
    while (true) {
    }
  }

  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);

  nfc.begin();
}

uint8_t message[13];

void get_card_data(void) {
  uint8_t i;

  // Serial.println("Listening...");
  if (nfc.inListPassiveTarget()) {
    // Serial.println("Something's there...");
    while (true) {
      message[0] = 0x00;
      message[1] = 0xA4;
      message[2] = 0x04;
      message[3] = 0x00;

      message[4] = 0x07;

      message[5] = 0xA0;
      message[6] = 0x00;
      message[7] = 0x00;
      message[8] = 0x01;
      message[9] = 0x02;
      message[10] = 0x03;
      message[11] = 0x04;

      message[12] = 0x00;

      uint8_t responseLength = sizeof(message);
      if (nfc.inDataExchange(message, responseLength, message, &responseLength)) {
        Serial.print("MESSAGE! ");
        Serial.print(responseLength);
        Serial.println();
        for (int i = 0; i < responseLength; i++) {
          Serial.print(message[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
        delay(10);
      } else {
        Serial.println("It's gone...");
        break;
      }
    }
  } else {
    Serial.print("Trying again...");
  }
}
