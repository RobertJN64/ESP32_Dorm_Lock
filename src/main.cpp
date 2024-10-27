#include <Arduino.h>
#include "lock.hpp"
#include "reader.hpp"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connected.");

  nfc_init();
}

void loop() {
  get_card_data(); // TODO - check if purdue ID
}