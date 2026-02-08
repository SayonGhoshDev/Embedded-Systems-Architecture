/*
 * Project: A.R.E.S. (Autonomous Robotic Exploration System)
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: Hybrid Control Firmware (Bluetooth + Autopilot)
 * Key Concept: Sensor Fusion, Signal Noise Cancellation, and Non-Blocking Logic
 * * * Engineering Challenges Solved:
 * 1. Navigation: Implemented 'Smart Turn' logic using differential PWM (140) to prevent 360-degree spinning.
 * 2. Sound Processing: Auto-Calibration algorithm calculates ambient noise baseline on boot to prevent false triggers.
 * 3. Safety Protocol: Rear lights act as functional brake/reverse lights using Active Low logic (< 200).
 */

#include <SoftwareSerial.h>
#include <Servo.h>

// --- PIN MAPPING (HARDWARE CONFIGURATION) ---
#define BT_RX 2
#define BT_TX 3
#define BUZZER 4
#define MOTOR_R_EN 5     // PWM Speed Control (Right)
#define MOTOR_L_EN 6     // PWM Speed Control (Left)
#define IN1 7            // Motor Driver Logic
#define IN2 8
#define IN3 9
#define IN4 10
#define SERVO_PIN 11     // Radar Servo
#define TRIG 12          // Sonar Trigger
#define ECHO 13          // Sonar Echo
#define IR_LEFT A0       // Cliff/Edge Sensor (Left)
#define SOUND_SENSOR A1  // Analog Microphone
#define LDR A2           // Light Dependent Resistor
#define HEADLIGHT A3     // Front LEDs
#define BACKLIGHT A4     // Rear LEDs
#define IR_RIGHT A5      // Cliff/Edge Sensor (Right)

// --- SYSTEM CONFIGURATION (CALIBRATION) ---
// Differential Drive Settings (Straight Line Correction)
const int SPEED_LEFT = 225;
const int SPEED_RIGHT = 255;

// Kinematic Tuning (90-Degree Turn Logic)
const int TURN_SPEED = 140; // Reduced PWM to prevent spinning
const int TURN_TIME = 300;  // Time (ms) required for ~90 degree pivot

// Signal Processing Variables
int soundBaseline = 0;      // Ambient Noise Level
const int TRIGGER_GAP = 50; // Dynamic Threshold (Spike Detection)
unsigned long lastClapTime = 0;

// System State Flags
SoftwareSerial BT(BT_RX, BT_TX);
Servo radar;
bool isAutoMode = false;
bool isStealthMode = false;
bool isReversing = false;

long duration, distance;

void setup() {
  // --- GPIO INITIALIZATION ---
  // Output Pins
  pinMode(MOTOR_L_EN, OUTPUT); pinMode(MOTOR_R_EN, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(HEADLIGHT, OUTPUT); pinMode(BACKLIGHT, OUTPUT);
  pinMode(TRIG, OUTPUT);
  
  // Input Pins
  pinMode(ECHO, INPUT);
  pinMode(IR_LEFT, INPUT); pinMode(IR_RIGHT, INPUT);
  pinMode(SOUND_SENSOR, INPUT);
  pinMode(LDR, INPUT);
  
  // Communication & Actuators
  BT.begin(9600);
  radar.attach(SERVO_PIN);
  radar.write(90); // Initialize Radar to Center

  // Initial State: Lights OFF
  digitalWrite(HEADLIGHT, LOW);
  digitalWrite(BACKLIGHT, LOW);

  // --- BOOT SEQUENCE: SOUND AUTO-CALIBRATION ---
  // Sample ambient noise for 1000ms to set baseline
  long totalNoise = 0;
  for(int i=0; i<100; i++) {
    totalNoise += analogRead(SOUND_SENSOR);
    delay(10);
  }
  soundBaseline = totalNoise / 100;
  
  // Visual Confirmation (Double Blink)
  digitalWrite(HEADLIGHT, HIGH); delay(200);
  digitalWrite(HEADLIGHT, LOW); delay(200);
  digitalWrite(HEADLIGHT, HIGH); delay(200);
  digitalWrite(HEADLIGHT, LOW);
  
  tone(BUZZER, 1000, 200); // System Ready Beep
}

void loop() {
  // ====================================================
  // 1. SIGNAL PROCESSING: SMART SOUND LOGIC (CLAP SWITCH)
  // ====================================================
  int currentSound = analogRead(SOUND_SENSOR);
  
  // Dynamic Spike Detection: |Current - Baseline| > Threshold
  if (abs(currentSound - soundBaseline) > TRIGGER_GAP) {
    
    // Software Debouncing (200ms)
    if (millis() - lastClapTime > 200) { 
      lastClapTime = millis();
      
      // Toggle Autopilot State
      isAutoMode = !isAutoMode; 
      
      // Feedback Logic
      if (isAutoMode) {
        if(!isStealthMode) tone(BUZZER, 1000, 100); // Start Beep
      } else {
        stopCar(); // Immediate Safety Stop
        if(!isStealthMode) tone(BUZZER, 2000, 300); // Stop Beep
      }
    }
  }

  // ====================================================
  // 2. SAFETY LOGIC: BACKLIGHT & IR MONITOR
  // ====================================================
  int leftIR = analogRead(IR_LEFT);
  int rightIR = analogRead(IR_RIGHT);

  if (!isStealthMode) {
     // Trigger Condition: IR value < 200 (Cliff/Void) OR Reversing
     if (leftIR < 200 || rightIR < 200 || isReversing) {
       digitalWrite(BACKLIGHT, HIGH);
     } else {
       digitalWrite(BACKLIGHT, LOW);
     }
  } else {
     digitalWrite(BACKLIGHT, LOW);
  }

  // Auto-Headlight Logic (LDR)
  if (!isStealthMode && analogRead(LDR) < 400) {
    digitalWrite(HEADLIGHT, HIGH);
  } else {
    digitalWrite(HEADLIGHT, LOW);
  }

  // ====================================================
  // 3. CONTROL INTERFACE: BLUETOOTH TELEMETRY
  // ====================================================
  if (BT.available()) {
    char cmd = BT.read();
    
    // Manual Override: Any manual command cancels Autopilot
    if (cmd == 'F' || cmd == 'f') { isAutoMode = false; moveForward(); }
    else if (cmd == 'B' || cmd == 'b') { isAutoMode = false; moveBackward(); }
    else if (cmd == 'L' || cmd == 'l') { isAutoMode = false; turnLeft(); }
    else if (cmd == 'R' || cmd == 'r') { isAutoMode = false; turnRight(); }
    else if (cmd == 'S' || cmd == 's') { isAutoMode = false; stopCar(); }
    else if (cmd == 'V' || cmd == 'v') { if(!isStealthMode) tone(BUZZER, 1000, 300); } 
    else if (cmd == 'U' || cmd == 'u') { isAutoMode = !isAutoMode; stopCar(); } 
    else if (cmd == 'D' || cmd == 'd') { isAutoMode = false; performDance(); }
    else if (cmd == 'X' || cmd == 'x') { isStealthMode = !isStealthMode; stopCar(); }
  }

  // ====================================================
  // 4. AUTONOMOUS NAVIGATION LOGIC (AI CORE)
  // ====================================================
  if (isAutoMode) {
    distance = getDistance();
    
    // Path Clear > 30cm
    if (distance > 30) {
      moveForward();
    } 
    // Obstacle Detected
    else {
      stopCar();
      if(!isStealthMode) tone(BUZZER, 1000, 100);
      
      // Step 1: Tactical Retreat
      moveBackward();
      delay(400); 
      stopCar();
      
      // Step 2: Environmental Scanning
      radar.write(180); delay(400); // Scan Left
      int leftDist = getDistance();
      
      radar.write(0);  delay(400); // Scan Right
      int rightDist = getDistance();
      
      radar.write(90);  delay(200); // Reset Head
      
      // Step 3: Decision Making (Pivot Turn)
      // Using Low Speed (140 PWM) for precision 90-degree alignment
      if (leftDist > rightDist) {
        turnLeft(); 
        delay(TURN_TIME); // 300ms
      } else {
        turnRight(); 
        delay(TURN_TIME); // 300ms
      }
      stopCar();
      delay(200); // Stabilization Delay
    }
  }
}

// ================= ACTUATOR CONTROL FUNCTIONS =================

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(MOTOR_L_EN, SPEED_LEFT);
  analogWrite(MOTOR_R_EN, SPEED_RIGHT);
  isReversing = false; 
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(MOTOR_L_EN, SPEED_LEFT);
  analogWrite(MOTOR_R_EN, SPEED_RIGHT);
  isReversing = true; // Triggers Backlight Logic
}

void turnLeft() {
  // Pivot Turn (Left Wheel Back, Right Wheel Forward)
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(MOTOR_L_EN, TURN_SPEED);
  analogWrite(MOTOR_R_EN, TURN_SPEED);
  isReversing = false;
}

void turnRight() {
  // Pivot Turn (Left Wheel Forward, Right Wheel Back)
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(MOTOR_L_EN, TURN_SPEED);
  analogWrite(MOTOR_R_EN, TURN_SPEED);
  isReversing = false;
}

void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(MOTOR_L_EN, 0);
  analogWrite(MOTOR_R_EN, 0);
  isReversing = false;
}

// --- ULTRASONIC SENSOR DRIVER ---
long getDistance() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long d = pulseIn(ECHO, HIGH, 30000); // Timeout 30ms
  if (d == 0) return 999; 
  return d * 0.034 / 2;
}

// --- ENTERTAINMENT MODE ---
void performDance() {
  if(isStealthMode) return;
  
  for(int k=0; k<2; k++) {
    tone(BUZZER, 600, 150);
    digitalWrite(HEADLIGHT, HIGH); digitalWrite(BACKLIGHT, LOW);
    turnLeft(); delay(300);
    
    tone(BUZZER, 800, 150);
    digitalWrite(HEADLIGHT, LOW); digitalWrite(BACKLIGHT, HIGH);
    turnRight(); delay(300);
  }
  stopCar();
  digitalWrite(HEADLIGHT, LOW); digitalWrite(BACKLIGHT, LOW);
}