# 🧠 Project A.R.E.S. (Autonomous Robotic Exploration System) - Phase 2

## 📋 Executive Summary
While Phase 1 established the physical body, **Phase 2** breathes life into the rover through **Advanced Firmware Architecture**. This phase focuses exclusively on **Software Intelligence**, implementing a Hybrid Control System that seamlessly transitions between Manual Telemetry (Bluetooth) and Autonomous Navigation. This document details the algorithmic logic, signal processing pipelines, and non-blocking multitasking protocols engineered for the ATmega328P.

---

## 🧭 1. Autonomous Navigation Logic (The "Smart-Turn" Heuristic)
### 📉 The Problem: Stochastic Movement & Spinning
Standard obstacle-avoidance robots often execute random, jerky turns when blocked, leading to disorientation or "infinite spin loops" where the robot traps itself in corners.

### 🛡️ The Solution: Deterministic Decision Tree
We engineered a **"Look-and-Compare" Algorithm** that mimics biological decision-making.
* **Scan Sequence:** Upon detecting an obstacle (<30cm), the rover halts and sweeps the Servo Radar to map Left ($180^\circ$) and Right ($0^\circ$) distances.
* **Comparator Logic:** The firmware computes the spatial delta (`Left_Dist` vs `Right_Dist`).
* **Kinematic Execution:**
    * Executes a precision **90° Pivot Turn** specifically towards the clearer path.
    * Utilizes a reduced **Turning PWM (140)** to prevent inertial overshot, ensuring accurate angular alignment.

---

## 🔊 2. Adaptive Signal Processing (Sound Interface)
### ⚠️ The Risk: Ambient Noise Interference
Fixed analog thresholds (e.g., `value > 500`) are unreliable. A threshold that works in a quiet room fails in a noisy hall, causing false triggers or unresponsiveness.

### 🔧 The Engineering Fix: Boot-Time Auto-Calibration
We implemented a **Dynamic Baseline Algorithm** that runs during the system boot sequence.
* **Sampling Matrix:** The CPU captures 100 samples of ambient noise during the first 1000ms of startup to calculate the `baseline` noise floor.
* **Spike Detection:** The Clap Switch logic relies on **Relative Amplitude** (`abs(Current - Baseline) > 50`) rather than absolute values.
* **Result:** The system adapts to any environment automatically without code recompilation.

---

## 🛡️ 3. Safety Protocols & Active Feedback
### 🌈 State-Aware Illumination Logic
To provide visual debugging feedback and safety warnings, the lighting system is tied to specific machine states via **Active Low/High Logic**:
* **Forward State:** Backlights are **Force-Disabled** to save power.
* **Hazard State:** Backlights activate automatically during:
    * **Reverse Gear:** Visual warning of backward motion.
    * **Emergency Stop:** Brake light indication.
    * **Cliff Detection:** Triggered when IR Sensors detect surface anomalies (Active Low `< 200`).
* **Stealth Mode:** A global interrupt flag that instantly kills all PWM signals to LEDs and Buzzers for silent operation.

---

## 💻 4. Firmware Architecture (Non-Blocking Core)
### 📉 The Problem: CPU Latency
Traditional `delay()` functions pause the entire processor, making the robot "blind" to emergency stop commands while executing a turn or waiting for a sensor.

### 🚀 The Solution: Asynchronous Event Handling
The firmware utilizes a **Polled Loop Architecture** relying on hardware timers.
* **Input Polling:** Bluetooth (UART), Sound, and IR sensors are polled continuously without blocking delays.
* **State Machine:** Boolean flags (`isAutoMode`, `isStealthMode`) manage system behavior, allowing instant mode switching (e.g., overriding Autopilot with a Manual Stop command instantly).

---

## 🚀 5. Integrated Software Modules (Status Report)
The following logic modules have been successfully coded, tested, and deployed in **Phase 2**:

| Logic Module | Algorithm Used | Status |
| :--- | :--- | :--- |
| **Pathfinding** | Differential Comparator (Left vs Right) | ✅ Active |
| **Motor Control** | PWM Trimmed Differential Drive | ✅ Active |
| **Voice/Clap** | Adaptive Baseline Calibration | ✅ Active |
| **Cliff Safety** | Analog Thresholding (< 200) | ✅ Active |
| **Telemetry** | SoftwareSerial UART (9600 Baud) | ✅ Active |
| **HMI Feedback** | Context-Aware LED/Buzzer Patterns | ✅ Active |

---
*Algorithm, Logic & Firmware by **Sayon Ghosh** | CSE Undergraduate*
