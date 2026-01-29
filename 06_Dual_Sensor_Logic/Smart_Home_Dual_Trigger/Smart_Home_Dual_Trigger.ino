/*
 * Project: Dual Sensor Smart Home Automation
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: Event-Driven Programming using Multiple ISRs
 * Key Concept: Dual Hardware Interrupts with Source Identification.
 * Logic:
 * - Pin 2 (IR) triggers Interrupt on FALLING edge (Hand Wave).
 * - Pin 3 (Sound) triggers Interrupt on CHANGE edge (Clap Sound).
 * - 'volatile' flags used to identify WHO triggered the system.
 * - Latching Logic (Toggle Switch) controls the High Voltage Relay.
 */

const int buzzerPin = 11;
const int ledPin = 9;
const int irPin = 2;      // Interrupt 0
const int soundPin = 3;   // Interrupt 1
const int relayPin = 7;   // Output to AC Load

// Volatile is mandatory for variables shared between ISR and Main Loop
volatile bool irTriggered = false;
volatile bool soundTriggered = false;

// System State Memory
bool isLightOn = false;
unsigned long lastTriggerTime = 0; // For Debouncing

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(soundPin, INPUT);
  pinMode(relayPin, OUTPUT);

  // Initial State: Relay OFF
  digitalWrite(relayPin, HIGH);

  Serial.begin(9600);
  
  // Boot Sequence Logs
  Serial.println("System is ON.");
  delay(1000);
  Serial.println("Calibrating Sensors...");
  
  // Visual Feedback during Boot
  for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH); delay(50);
      digitalWrite(ledPin, LOW); delay(50);
  }
  
  Serial.println("System Ready: Wave Hand OR Clap!");
  
  // Attaching the Interrupt Vectors
  attachInterrupt(digitalPinToInterrupt(irPin), irManager, FALLING);
  attachInterrupt(digitalPinToInterrupt(soundPin), soundManager, CHANGE);
}

void loop() {
  // Case 1: Hand Wave Detected (IR)
  if (irTriggered == true) {
    Serial.println("-----------------------------");
    Serial.println("👉 Source: IR SENSOR (Hand Wave)");
    toggleLight();
    irTriggered = false; // Reset Flag
  }
  // Case 2: Clap Sound Detected (Mic)
  else if(soundTriggered == true) {
    Serial.println("-----------------------------");
    Serial.println("👏 Source: SOUND SENSOR (Clap)");
    toggleLight();
    soundTriggered = false; // Reset Flag
  }
}

// --- Action Function (Controls AC Load) ---
void toggleLight() {
  // Debounce Logic (Ignore trigger if < 200ms)
  if (millis() - lastTriggerTime > 200) {
    lastTriggerTime = millis();
    
    isLightOn = !isLightOn; // Toggle State
      
    if (isLightOn == true) {
      digitalWrite(relayPin, LOW); // Relay ON
      Serial.println("Result: LIGHT ON [AC Active]");
      
      // Feedback: Single Beep
      digitalWrite(buzzerPin, HIGH); digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
    }
    else {
      digitalWrite(relayPin, HIGH); // Relay OFF
      Serial.println("Result: LIGHT OFF [AC Inactive]");
    
      // Feedback: Double Beep
      digitalWrite(buzzerPin, HIGH); digitalWrite(ledPin, LOW);
      delay(100); digitalWrite(buzzerPin, LOW);
      delay(100); digitalWrite(buzzerPin, HIGH);
      delay(100); digitalWrite(buzzerPin, LOW);
    }
  }
  
  // Safety Cool-down
  delay(1000);
}

// --- Interrupt Service Routines (ISRs) ---
void irManager() {
  if (soundTriggered == false) irTriggered = true;
}

void soundManager() {
  if (irTriggered == false) soundTriggered = true;
}