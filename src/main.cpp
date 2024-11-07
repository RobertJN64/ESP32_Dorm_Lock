#include <Arduino.h>

#include "reader.hpp"
#include "lock.hpp"
#include "db.hpp"

#define PIN_MODE_ADD 5
#define PIN_MODE_RM 18
#define PIN_MODE_CHK 19

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connected.");

  pinMode(PIN_MODE_ADD, INPUT_PULLUP);
  pinMode(PIN_MODE_RM, INPUT_PULLUP);
  pinMode(PIN_MODE_CHK, INPUT_PULLUP);

  db_init();
  nfc_init();
}

void loop() {
  String resp = get_card_data();
  if (resp != "") {
    Serial.println("got data");
    Serial.println(resp);

    if (!digitalRead(PIN_MODE_ADD)) {
      add_id(resp);
    } else if (!digitalRead(PIN_MODE_RM)) {
      rm_id(resp);
    } else if (!digitalRead(PIN_MODE_CHK)) {
      if (check_id(resp)) {
        Serial.println("Valid code tapped - unlocking!");
        unlock();
        delay(5000);
        lock();
        delay(100);
      } else {
        Serial.println("Invalid code tapped!");
      }
    } else {
      Serial.println("No mode active");
    }
  } else {
    Serial.println("no data...");
  }
}