#include <Arduino.h>
#include <Stepper.h>

#define stepsPerRevolution 2048 // change this to fit the number of steps per revolution

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 13, 14, 12, 27);

void setup() {
  Serial.begin(115200);
  delay(1000);
  myStepper.setSpeed(15); // 60 rpm
  Serial.println("Connected.");
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(3 * stepsPerRevolution);
  Serial.println("done");
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-3 * stepsPerRevolution);
  Serial.println("done");
  delay(500);
}