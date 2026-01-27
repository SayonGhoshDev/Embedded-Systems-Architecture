/*
 * Project: Synchronized Actuator Control System
 * Author: Sayon Ghosh (CSE Student)
 * Logic: Linear Interpolation (Mapping) to sync mechanical and electrical outputs.
 */

#include <Servo.h>

Servo myservo;

// Hardware Pin Configuration
const int servoPin = 11; // PWM Pin for Motor
const int ledPin = 6;    // PWM Pin for LED
const int potPin = A0;   // Analog Input

void setup (){
  myservo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int potValue = analogRead(potPin); // Raw Data: 0-1023

  // Data Processing: Mapping ADC value to Actuator Limits
  int angle = map(potValue, 0, 1023, 0, 180);      // Mechanical Limit
  int brightness = map(potValue, 0, 1023, 0, 255); // Electrical Limit (8-bit)

  // Execution
  myservo.write(angle);
  analogWrite(ledPin, brightness);

  // Data Logging
  Serial.print("Raw Input: ");
  Serial.print(potValue);
  Serial.print(" | Servo Angle: ");
  Serial.print(angle);
  Serial.print(" | LED PWM: ");
  Serial.println(brightness);

  delay(15); // Stabilization delay for Servo Gearbox
}