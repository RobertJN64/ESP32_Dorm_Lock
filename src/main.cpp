#include <Arduino.h>

#include "reader.hpp"
#include "lock.hpp"
#include "db.hpp"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connected.");

  // nfc_init();
  Serial.println(check_id("hello"));
  add_id("hello");
  Serial.println(check_id("hello"));
  add_id("goodbye");
  rm_id("hello");
  Serial.println(check_id("hello"));
}

void loop() {
  // if (get_card_data()) {
  //   Serial.println("Valid code tapped - unlocking!");
  //   unlock();
  //   delay(5000);
  //   lock();
  //   delay(100);
  // }
}