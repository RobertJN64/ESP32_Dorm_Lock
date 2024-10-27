#include <Arduino.h>
#include <Stepper.h>

#define stepsPerRevolution 2048 // change this to fit the number of steps per revolution

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 13, 14, 12, 27);

void unlock() {
  Serial.println("clockwise");
  myStepper.setSpeed(15); // 60 rpm
  myStepper.step(3 * stepsPerRevolution);
  Serial.println("done");
  delay(500);
}

void lock() {
  Serial.println("counterclockwise");
  myStepper.setSpeed(15); // 60 rpm
  myStepper.step(-3 * stepsPerRevolution);
  Serial.println("done");
  delay(500);
}