/*
 * Project: Hardware Interrupt Security System
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: Event-Driven Programming using ISR (Interrupt Service Routine)
 * Key Concept: replacing 'Polling' with 'Hardware Interrupts' for instant response.
 * Logic:
 * - Pin 2 triggers an Interrupt on FALLING edge (High to Low signal).
 * - 'volatile' variable is used for safe memory access during ISR execution.
 */

const int buzzerPin = 9;
const int ledPin = 10;
const int irsensorPin = 2; // Must be Pin 2 or 3 for Arduino Uno Interrupts

// Volatile is mandatory for variables shared between ISR and Main Loop
volatile bool detectionFound = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(irsensorPin, INPUT);

  Serial.begin(9600);
  
  // Boot Sequence Logs
  Serial.println("System is ON.");
  delay(1000);
  Serial.println("Now Preparing for Searching.");
  delay(2000);
  
  Serial.println("Searching...");
  
  // Attaching the Interrupt Vector
  // When Pin 2 goes from HIGH to LOW (Falling), 'catchThief' function runs immediately.
  attachInterrupt(digitalPinToInterrupt(irsensorPin), catchThief, FALLING);
}

void loop() {
  // The main loop is passive regarding the sensor. 
  // It only reacts when the ISR flag is set to TRUE.
  if (detectionFound == true) {
    Serial.println("Found!... Someone or Something is there. Please be aware!");

    // Alarm Sequence
    for (int i = 0; i < 5; i++) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW);
      delay(100);
    }

    // Reset Sequence
    detectionFound = false;
    Serial.println("Preparing for Next Searching! ... ... ...");
    delay(1000);
    
    Serial.println("Searching...");
  }
}

// --- Interrupt Service Routine (ISR) ---
// This function runs independently of the main loop.
void catchThief () {
  detectionFound = true;
}