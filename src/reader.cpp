#include <Wire.h>
#include <Adafruit_PN532.h>

Adafruit_PN532 nfc(2, 3);
uint8_t message[] = {
    0x00, // standard command
    0xA4, // instruction (read)
    0x04, // p1
    0x00, // p2

    0x07, // AID len

    0xA0, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, // AID

    0x00 // terminator
};
uint8_t response[32];

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

String get_card_data() {
  bool got_valid_code = false;

  if (nfc.inListPassiveTarget()) {
    while (true) {
      uint8_t responseLength = sizeof(response); // this must be initialized
      if (nfc.inDataExchange(message, sizeof(message), response, &responseLength)) {
        response[responseLength] = '\0';
        return (char *)response;
      } else {
        break; // device now out of range
      }
    }
  }
  return ""; // no device
}
