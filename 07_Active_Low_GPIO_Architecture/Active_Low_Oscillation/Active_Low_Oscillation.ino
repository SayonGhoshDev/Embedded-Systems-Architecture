/*
 * Project: IoT Phase 2 - Active Low Architecture Validation
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: Tensilica Xtensa GPIO Register Manipulation
 * Key Concept: Current Sink Topology (Active Low Logic)
 * * Engineering Logic:
 * - Unlike Arduino (AVR) which uses Active HIGH (Source Current), 
 * NodeMCU uses Active LOW (Sink Current) for on-board peripherals.
 * - Logic 0 (LOW) -> Complete Circuit (GND) -> LED ON.
 * - Logic 1 (HIGH) -> Break Circuit (3.3V) -> LED OFF.
 */

// Mapping: D4 on NodeMCU Board = GPIO 02 on ESP8266 Chip
// This pin is physically hardwired to the Internal Blue LED.
const int statusLED = D4; 

void setup() {
  // Initialize GPIO 2 as Output (Push-Pull Configuration)
  pinMode(statusLED, OUTPUT);
  
  // Debugging Port
  Serial.begin(115200);
  Serial.println("\n--- SYSTEM BOOT ---");
  Serial.println("Architecture: ESP8266 Active Low Test");
  Serial.println("Status: Oscillation Started");
}

void loop() {
  // PHASE 1: SINK CURRENT (Logic 0)
  // The LED Anode is at 3.3V. Providing LOW (0V) completes the circuit.
  digitalWrite(statusLED, LOW);   
  Serial.println("State: ON  [Current Sinking]");
  delay(1000); // 1000ms Blocking Delay

  // PHASE 2: SOURCE CURRENT (Logic 1)
  // The LED Anode is at 3.3V. Providing HIGH (3.3V) creates 0V Potential Difference.
  digitalWrite(statusLED, HIGH);  
  Serial.println("State: OFF [Potential Equalized]");
  delay(1000); // 1000ms Blocking Delay
}