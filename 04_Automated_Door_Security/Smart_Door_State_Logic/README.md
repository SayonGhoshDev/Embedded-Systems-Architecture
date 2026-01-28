# 🔒 Automated Smart Door Security System

## 🎯 Objective
To design a robust access control system that integrates **Sensor Fusion** (Ultrasonic Input) with **Mechanical Actuation** (Servo Motor). The core objective is to implement **Finite State Machine (FSM)** logic to manage the door's status efficiently, avoiding redundant processing and mechanical jitter.

## 🧠 Engineering Logic & Architecture

### 1. Finite State Machine (FSM)
Unlike simple "if-else" loops, this system uses a **Boolean Flag (`isDoorOpen`)** as a 1-bit memory.
* **Problem:** Without state memory, the processor would repeatedly command the motor to "Open" thousands of times per second even if it is already open.
* **Solution:** The actuator is only triggered when a **Change of State** is required (e.g., `Closed -> Open`).

### 2. Hysteresis (Stability Gap)
To prevent the door from oscillating wildly when a user stands at the threshold distance, a **Dead Band** is implemented:
* **Entry Trigger:** Distance < 10cm
* **Exit Trigger:** Distance > 15cm
* **Result:** The 5cm gap ensures mechanical stability and prevents "phantom triggering" due to sensor noise.

### 3. Slew Rate Control
Instead of instant servo movement (which causes high current spikes and gear stress), the code uses a logical loop with micro-delays (`delay(15)`) to create a smooth, hydraulic-like motion profile.

## 🛠️ Hardware Stack
* **Microcontroller:** Arduino Uno (ATmega328P)
* **Input:** HC-SR04 Ultrasonic Sensor
* **Actuator:** SG90 Micro Servo Motor
* **Feedback:** Active Buzzer & Status LED

---
*Developed by **Sayon Ghosh** | CSE Undergraduate*
