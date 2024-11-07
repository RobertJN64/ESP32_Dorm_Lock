#include <Arduino.h>

#include "reader.hpp"
#include "lock.hpp"
#include "db.hpp"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connected.");

  db_init();
  nfc_init();
}

void loop() {
  String resp = get_card_data();
  if (resp != "") {
    Serial.println("got data");
    Serial.println(resp);

    if () {
      add_id(resp);
    } else if () {
      rm_id(resp)
    } else if () {
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