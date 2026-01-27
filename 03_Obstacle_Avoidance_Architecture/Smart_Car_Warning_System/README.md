# Hybrid Time-Control Obstacle Avoidance System 🦇🚗

## 📜 Overview
A proximity detection system designed for autonomous vehicles. This module replaces standard blocking delays with a **Hybrid State Machine**, utilizing both `millis()` for multitasking warnings and blocking logic for critical safety interventions.

## 🧠 Engineering Logic
* **Sensor Physics:** Uses Ultrasonic waves (40kHz) to calculate distance based on Time-of-Flight (ToF).
  * Formula: $Distance = \frac{Speed_{sound} \times Time_{echo}}{2}$
* **Zone-Based Decision Making:**
  1.  **Safe Zone (>30cm):** Idle state.
  2.  **Caution Zone (15-30cm):** Non-blocking intermittent alert (uses `millis()` timer).
  3.  **Critical Zone (<15cm):** Immediate blocking override (Stop command).

## 🛠️ Hardware Requirements
* HC-SR04 Ultrasonic Sensor (Trig: D9, Echo: D10)
* Active Buzzer (D11)
* Status LED (D5)

## 🚀 Key Feature: Non-Blocking Polling
Unlike traditional loop delays, this code uses a time-delta calculation (`currentMillis - previousMillis`) to toggle the alarm while continuously polling the sensor for new data.
