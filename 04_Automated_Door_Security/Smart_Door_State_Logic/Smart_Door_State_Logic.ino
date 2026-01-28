/*
 * Project: Automated Smart Door Security System
 * Author: Sayon Ghosh (CSE Student)
 * Architecture: Finite State Machine (FSM) with Boolean Logic
 * Key Concept: Hysteresis (Dead Band) to prevent mechanical jitter.
 * * Logic Flow:
 * - The system uses a 'State Variable' (bool) to track if the door is Open/Closed.
 * - It implements a 'Dead Band' (10cm vs 15cm) to prevent oscillation.
 */

#include <Servo.h>

Servo myServo;

// Hardware Pin Configuration
const int buzzerPin = 3;
const int ledPin = 5;
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;

// Global Variables
long duration;
int distance;

// State Machine Variable (1-Bit Memory)
bool isDoorOpen = false; 

void setup() {
  // Servo Initialization
  myServo.attach(servoPin);
  myServo.write(0); // Initial State: Closed
  delay(500);       // Mechanical settling time

  // Pin Configuration
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("System Initialized: Security Protocol Active.");
}

void loop(){
  // --- SENSOR DRIVER LOGIC (Ultrasonic) ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  // Physics: Distance = (Time * Speed of Sound) / 2
  distance = duration * 0.034 / 2;

  Serial.print("Target Distance: ");
  Serial.print(distance);
  Serial.print(" cm");

  // --- FINITE STATE MACHINE (FSM) LOGIC ---
  
  // STATE 1: ENTRY SEQUENCE
  // Condition: Visitor is close (<10cm) AND Door is currently Closed (False)
  if (distance < 10 && isDoorOpen == false) {
    Serial.println(" | [EVENT] Valid Entry Detected. Executing Sequence...");

    // Feedback
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);

    // Actuator: Slew Rate Control for Smooth Opening
    for (int pos = 0; pos <= 180; pos += 2) {
      myServo.write(pos);
      delay(15);
    }
    
    // Update System Memory
    isDoorOpen = true; 
    Serial.println(" | [STATE UPDATE] Door Status: OPEN");
  }

  // STATE 2: EXIT SEQUENCE
  // Condition: Visitor is far (>15cm) AND Door is currently Open (True)
  // Note: The 5cm gap (10-15) is the Hysteresis zone to ensure stability.
  else if (distance > 15 && isDoorOpen == true) {
    Serial.println(" | [EVENT] Visitor Left. Waiting for timeout...");
    delay(2000); // Safety Timeout

    Serial.println(" | [ACTION] Securing Door...");
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    // Actuator: Smooth Closing
    for (int pos = 180; pos >= 0; pos -= 2) {
      myServo.write(pos);
      delay(15);
    }
    
    // Update System Memory
    isDoorOpen = false;
    Serial.println(" | [STATE UPDATE] Door Status: CLOSED");
  }

  else {
    Serial.println(" | [STATUS] Standby");
  }
  
  delay(100); // Loop stability delay
}