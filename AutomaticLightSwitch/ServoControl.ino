#include <Servo.h>

Servo servo;

const int servoPin = 12; // D6
const int onVal = 115;
const int offVal = 20;
const int midVal = 65;
int switchDelay = 200;

void setupServo() {
  servo.attach(servoPin);
  servo.write(midVal);
  delay(500);
  servo.detach();
}

void toggleTest() {
  ArduinoOTA.handle();
  switchOn();
  ArduinoOTA.handle();
  delay(3000);
  ArduinoOTA.handle();
  switchOff();
  ArduinoOTA.handle();
  delay(3000);
  ArduinoOTA.handle();
}

void switchOn() {
  servo.attach(servoPin);
  servo.write(onVal);
  delay(switchDelay);
  servo.write(midVal);
  delay(400);
  servo.write(midVal + 20); //fixes servo jerk on detach
  delay(10);
  servo.detach();
}

void switchOff() {
  servo.attach(servoPin);
  servo.write(offVal);
  delay(switchDelay);
  servo.write(midVal-5);
  delay(400);
  servo.detach();
}
