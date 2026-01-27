/*
 * Project: Intelligent Obstacle Avoidance Warning System
 * Author: Sayon Ghosh (CSE Student)
 * Architecture: Hybrid Time Control (Blocking + Non-Blocking Logic)
 * Sensors: HC-SR04 Ultrasonic Sensor
 */

const int ledPin = 5;
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 11;

long duration;
int distance;

// Timer Variables for Multitasking
unsigned long previousMillis = 0;
const long interval = 200; // Frequency of Warning Beeps
int buzzerState = LOW;

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  unsigned long currentMillis = millis(); // Capture System Uptime

  // --- SENSOR DRIVER LOGIC ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  // Physics Formula: Distance = (Time * Speed of Sound) / 2
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");

  // --- DECISION MAKING ALGORITHM ---
  
  // CASE 1: CRITICAL DANGER (< 15cm)
  if (distance < 15) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);

    Serial.println(" | 👋 STOP! CRASH IMMINENT! Open your Eyes! 😳");
    delay(500); // Blocking alert for safety
  }
  
  // CASE 2: CAUTION ZONE (15cm - 30cm)
  else if (distance < 30) {
    // Non-Blocking Logic (Millis) for multitasking warning
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      // Toggle State
      if (buzzerState == LOW) {
        buzzerState = HIGH;
      } else {
        buzzerState = LOW;
      }
      digitalWrite(buzzerPin, buzzerState);
      digitalWrite(ledPin, buzzerState);
    }
    Serial.println(" | ⚠️ CAUTION! SLOW DOWN. Stay Alert. 😐");
  }
  
  // CASE 3: SAFE ZONE (> 30cm)
  else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    
    Serial.println(" | 🚶 SAFE ROAD! Enjoy the Ride 😊❤️");
    delay(500);
  }

  delay(100); // System Stability Delay
}