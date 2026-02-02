/*
 * Project: A.R.E.S. (Autonomous Robotic Exploration System)
 * Module: Propulsion Unit (Motor Logic Test)
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: Active Low Logic Implementation
 * Key Concept: H-Bridge Control & GPIO Sink Logic
 * * * Engineering Logic:
 * - The NodeMCU uses 3.3V logic, while the L298N controls 12V motors.
 * - Challenge: Direct GPIO control sometimes fails due to current limits.
 * - Solution: Implemented "Active Low" Logic for LED indicators on D4
 * to match the boot-safe configuration (Pull-up behavior).
 * - Motor Logic:
 * - Forward: IN1 HIGH, IN2 LOW
 * - Backward: IN1 LOW, IN2 HIGH
 * - Stop: IN1 LOW, IN2 LOW
 */

// Pin Definitions (A.R.E.S. Hardware Map)
int in1 = D1;        // Motor Input 1
int in2 = D2;        // Motor Input 2
int rearLight = D4;  // Red LED (Active Low Logic)
int headLight = D6;  // Yellow LED (Active High Logic)
int indicator = D7;  // Green LED (Active High Logic)

void setup() {
  // Initialize Motor Control Pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Initialize LED Indicators
  pinMode(rearLight, OUTPUT);
  pinMode(headLight, OUTPUT);
  pinMode(indicator, OUTPUT);

  // Initial State: Safe Mode (Everything OFF)
  digitalWrite(rearLight, HIGH);   // Active Low: HIGH = OFF
  digitalWrite(headLight, LOW);    // Active High: LOW = OFF
  digitalWrite(indicator, LOW);    // Active High: LOW = OFF

  Serial.begin(115200);
  Serial.println("\n[System] A.R.E.S. Propulsion Logic Ready!");
}

void loop() {
  // --- STATE 1: FORWARD MOTION (CRUISE) ---
  Serial.println("[ARES] Moving Forward -> Headlights ON");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // Visuals
  digitalWrite(headLight, HIGH); // Headlight ON
  digitalWrite(rearLight, HIGH); // Rear Light OFF (Active Low)
  digitalWrite(indicator, LOW);  // Indicator OFF
  delay(2000);

  // --- STATE 2: STOP (IDLE) ---
  Serial.println("[ARES] Stopping -> Indicators Blinking");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  // Visuals
  digitalWrite(headLight, LOW);  // Headlight OFF
  digitalWrite(rearLight, HIGH); // Rear Light OFF
  
  // Blinking Effect (Parking Mode)
  for (int i=0; i<3; i++) {
      digitalWrite(indicator, HIGH);
      delay(200);
      digitalWrite(indicator, LOW);
      delay(200);
  }
  delay(500);

  // --- STATE 3: BACKWARD MOTION (RETREAT) ---
  Serial.println("[ARES] Moving Backward -> Rear Lights ON");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Visuals
  digitalWrite(headLight, LOW);  // Headlight OFF
  digitalWrite(rearLight, LOW);  // Rear Light ON (Active Low: LOW = ON)
  digitalWrite(indicator, LOW);  // Indicator OFF
  delay(2000);

  // --- STATE 4: STOP (RESET) ---
  Serial.println("[ARES] Mission Cycle Complete. Resetting...");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(rearLight, HIGH); // OFF
  
  // Blinking Effect
  for (int i=0; i<3; i++) {
      digitalWrite(indicator, HIGH);
      delay(200);
      digitalWrite(indicator, LOW);
      delay(200);
  }
  delay(500);
}