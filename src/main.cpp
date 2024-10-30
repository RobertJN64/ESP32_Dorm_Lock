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
  if (get_card_data()) {
    Serial.println("Valid code tapped - unlocking!");
    unlock();
    delay(5000);
    lock();
    delay(100);
  }
}