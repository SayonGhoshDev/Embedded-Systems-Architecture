/*
 * Project: OMNI-SENTINEL (Multi-Sensor Fusion System)
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: Hybrid GPIO Logic (Active High + Active Low)
 * Key Concept: Non-Blocking Sensor Polling & Analog Peak Detection
 * * * Engineering Challenges Solved:
 * 1. Boot Safety: Using Pull-up wiring for D3/D4 to prevent boot failure.
 * 2. Sound Sampling: Implemented 50ms listening window for accurate clap detection.
 * 3. Sensor Fusion: Integrating Vision (Sonar), Touch (IR), Sound (Mic), and Thermal (DHT) data simultaneously.
 */

#include <ESP8266WiFi.h>
#include <DHT.h>

// --- PIN MAPPING (CRITICAL) ---
#define RED_LED D0      // Active High (Visual Danger)
#define IR_PIN D1       // Input (Touch)
#define SOUND_ANALOG A0 // Analog Input (Audio Sampling)
#define YELLOW_LED D3   // Active Low (Heat Warning) - Critical Boot Pin
#define GREEN_LED D4    // Active Low (Clap Indicator) - Critical Boot Pin
#define TRIG_PIN D5     // Ultrasonic Output
#define ECHO_PIN D6     // Ultrasonic Input
#define DHT_PIN D7      // Thermal Data
#define BUZZER_PIN D8   // Active High (Alarm) - Critical Boot Pin

// --- SENSOR OBJECTS ---
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// --- CONFIGURATION ---
const int SOUND_THRESHOLD = 400; // Calibrated Value for Clap
unsigned long previousMillis = 0;
const long interval = 2000;      // DHT Polling Interval

void setup() {
  Serial.begin(115200);

  // Output Configuration
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);

  // Input Configuration
  pinMode(IR_PIN, INPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initial States (Safety Logic)
  digitalWrite(RED_LED, LOW);     // OFF
  digitalWrite(BUZZER_PIN, LOW);  // OFF
  digitalWrite(YELLOW_LED, HIGH); // OFF (Active Low)
  digitalWrite(GREEN_LED, HIGH);  // OFF (Active Low)

  dht.begin();
  
  Serial.println("\n\n--- SYSTEM OMNI-SENTINEL ONLINE ---");
  Serial.println("Sensors: Sonar | IR | Analog Mic | Thermal");
  
  // Boot Sequence Animation
  digitalWrite(RED_LED, HIGH); delay(200); digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW); delay(200); digitalWrite(GREEN_LED, HIGH);
}

void loop() {
  // 1. RADAR VISION (Ultrasonic)
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 10) {
    digitalWrite(RED_LED, HIGH); // Intruder Alert
  } else {
    digitalWrite(RED_LED, LOW);
  }

  // 2. TACTILE SENSE (IR Sensor)
  if (digitalRead(IR_PIN) == LOW) {
    digitalWrite(BUZZER_PIN, HIGH); // Contact Alarm
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // 3. AUDITORY SENSE (Analog Peak Detection)
  int signalMax = 0;
  int signalMin = 1024;
  unsigned long startMillis = millis(); 
  
  // 50ms Sampling Window
  while (millis() - startMillis < 50) {
    int sample = analogRead(SOUND_ANALOG);
    if (sample > signalMax) signalMax = sample;
    if (sample < signalMin) signalMin = sample;
  }
  int peakToPeak = signalMax - signalMin; // Amplitude

  if (peakToPeak > SOUND_THRESHOLD) {
    digitalWrite(GREEN_LED, LOW); // Active Low ON
    Serial.print("👏 CLAP DETECTED! Val: "); 
    Serial.println(peakToPeak);
    delay(100); 
  } else {
    digitalWrite(GREEN_LED, HIGH); // OFF
  }

  // 4. THERMAL SENSE (DHT11 - Non-Blocking)
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t)) {
      Serial.print("Temp: "); Serial.print(t); Serial.println("C");
      if (t > 30) { 
        digitalWrite(YELLOW_LED, LOW); // Heat Warning (Active Low)
        Serial.println("🔥 HEAT WARNING!");
      } else {
        digitalWrite(YELLOW_LED, HIGH);
      }
    }
  }
}