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

void readNdefTextMessage(uint8_t *buf) {
  // Assumes NDEF message starts at buf[0]
  uint8_t textLen = buf[7]; // The length of the text payload
  char message[128];

  // Copy the text payload (starting at buf[8] where the text starts)
  memcpy(message, &buf[8], textLen);
  message[textLen] = '\0'; // Null-terminate the string

  // Print the NDEF text message
  Serial.print("Text message: ");
  Serial.println(message);
}

void loop() {
  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // Buffer to store the returned UID
  uint8_t uidLength;                     // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Found a card
    Serial.println("Found an NFC tag!");

    // Print UID
    Serial.print("UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(" 0x");
      Serial.print(uid[i], HEX);
    }
    Serial.println("");

    // Attempt to read data from the card
    uint8_t ndefBuf[128]; // Buffer to hold NDEF data
    uint8_t ndefSize = sizeof(ndefBuf);

    success = nfc.ntag2xx_ReadPage(4, ndefBuf);
    if (success) {
      Serial.println("NDEF Data found:");
      for (uint8_t i = 0; i < ndefSize; i++) {
        Serial.print(ndefBuf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      // Attempt to decode the NDEF message if it is a text message
      if (ndefBuf[0] == 0x03) { // 0x03 means NDEF format
        Serial.println("Reading NDEF text message...");
        readNdefTextMessage(ndefBuf);
      } else {
        Serial.println("NDEF message not recognized.");
      }
    } else {
      Serial.println("Failed to read NDEF data.");
    }

    const char *url = "adafruit.com/blog/";
    uint8_t ndefprefix = NDEF_URIPREFIX_HTTP_WWWDOT;

    Serial.println(nfc.mifareclassic_WriteNDEFURI(1, ndefprefix, url));

    // Wait a bit before scanning again
    delay(1000);
  }
}