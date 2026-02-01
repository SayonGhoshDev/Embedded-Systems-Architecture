/*
 * Project: A.R.E.S. Prototype - Wireless Servo Telemetry
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: UART Emulation (SoftwareSerial) + PWM
 * Key Concept: Wireless Actuation & Latency-Free Control
 * * * Engineering Logic:
 * - NodeMCU has limited Hardware Serial ports (UART0 is used for USB).
 * - To communicate with Bluetooth (HC-05) while debugging, we use
 * SoftwareSerial to emulate a secondary UART port on GPIOs D2 & D3.
 * - This allows simultaneous "Over-the-Air" control and Serial Monitoring.
 */

#include <Servo.h>
#include <SoftwareSerial.h>

// --- PIN CONFIGURATION ---
// HC-05 TX -> NodeMCU D2 (GPIO 4) [Soft RX]
// HC-05 RX -> NodeMCU D3 (GPIO 0) [Soft TX]
SoftwareSerial BTSerial(D2, D3); 

Servo myServo;
const int servoPin = D4; // GPIO 2

void setup() {
  Serial.begin(115200);   // For PC Debugging
  BTSerial.begin(9600);   // For HC-05 Communication

  myServo.attach(servoPin);
  myServo.write(90); // Initialize at Center

  Serial.println("\n[System] A.R.E.S. Neck Mechanism Ready.");
  Serial.println("[Mode] Waiting for Bluetooth Commands...");
  BTSerial.println("CONNECTED: NodeMCU Servo Controller Online");
}

void loop() {
  // Check for incoming Bluetooth Data
  if (BTSerial.available()) {
    char command = BTSerial.read(); // Read single byte
    Serial.print("[RX] Command: ");
    Serial.println(command);

    // --- ACTUATION LOGIC ---
    
    // Look Left
    if (command == 'L' || command == 'l') { 
      myServo.write(180); 
      BTSerial.println("ACK: Rotating Left (180)");
    }
    
    // Look Right
    else if (command == 'R' || command == 'r') { 
      myServo.write(0); 
      BTSerial.println("ACK: Rotating Right (0)");
    }
    
    // Center Align
    else if (command == 'C' || command == 'c') { 
      myServo.write(90); 
      BTSerial.println("ACK: Centered (90)");
    }
    
    // Auto-Sweep (LIDAR Simulation)
    else if (command == 'S' || command == 's') {
      BTSerial.println("MODE: Scanning Area...");
      // Sweep 0 to 180
      for (int pos = 0; pos <= 180; pos += 5) {
        myServo.write(pos);
        delay(20);
      }
      // Sweep 180 to 0
      for (int pos = 180; pos >= 0; pos -= 5) {
        myServo.write(pos);
        delay(20);
      }
      myServo.write(90); // Reset
      BTSerial.println("STATUS: Scan Complete");
    }
  }
}