// photoRADAR
//
// Sweeps a servo-mounted phototransistor across 180° and streams
// angle,intensity readings over serial for the web dashboard to plot.
//
// Based on the Arduino Student Kit, Lesson 9: Light Wave Radar

#include <Servo.h>

const int sensorPin = A0;  // phototransistor voltage-divider tap
const int servoPin = 3;    // servo signal (white) wire

int servoAngle = 0;  // starts at 0 degrees
int increment = 3;   // degrees per step: lower = finer resolution, slower sweep

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(servoAngle);
  delay(1000);  // give the servo time to reach the starting position
}

void loop() {
  // sweep forward, then back, so the servo doesn't snap to 0 between passes
  for (servoAngle = 0; servoAngle <= 180; servoAngle += increment) {
    sweep();
  }
  for (servoAngle = 180; servoAngle >= 0; servoAngle -= increment) {
    sweep();
  }
}

// move to the current angle, take a reading, and print it as "angle,intensity"
void sweep() {
  myServo.write(servoAngle);
  delay(100);  // let the servo settle before reading
  int lightAmount = analogRead(sensorPin);
  Serial.print(servoAngle);
  Serial.print(",");
  Serial.println(lightAmount);
}
