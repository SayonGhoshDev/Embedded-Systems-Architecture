# 🦾 Project A.R.E.S. (Autonomous Robotic Exploration System)

![Status](https://img.shields.io/badge/Status-Completed-success)
![Hardware](https://img.shields.io/badge/Hardware-ATmega328P_%7C_L298N-blue)
![Language](https://img.shields.io/badge/Firmware-C%2B%2B_%28Embedded%29-orange)

## 📋 Executive Summary
**Project A.R.E.S.** represents a comprehensive engineering initiative to design a scalable, autonomous rover platform capable of **Environmental Sensing**, **Remote Telemetry**, and **Real-Time Decision Making**. 

Bridging the gap between robust **Electro-Mechanical Engineering (Phase 1)** and **Advanced Firmware Intelligence (Phase 2)**, this system demonstrates a Hybrid Control Architecture. It seamlessly transitions between manual Bluetooth telemetry and autonomous navigation using a non-blocking, event-driven core.

---

## 📸 System Gallery

| **Front Profile (Vision System)** | **Top Architecture (Component Matrix)** |
| :---: | :---: |
| ![Front View](Project_A.R.E.S_Rover/Phase_2_Software_Architecture/Assets/ares_rover_front.jpeg) | ![Top View](Project_A.R.E.S_Rover/Phase_2_Software_Architecture/Assets/ares_top_architecture.jpeg) |

| **Rear Wiring Topology** | **Side Kinematics** |
| :---: | :---: |
| ![Rear View](Project_A.R.E.S_Rover/Phase_2_Software_Architecture/Assets/ares_rear_wiring_logic.jpeg) | ![Side View](Project_A.R.E.S_Rover/Phase_2_Software_Architecture/Assets/ares_side_profile.jpeg) |

---

## 🛠️ System Architecture Overview

The project is divided into two distinct development phases. Click the headers below to view the detailed documentation for each phase.

### 📂 [Phase 1: Electro-Mechanical Architecture](./Project_A.R.E.S_Rover/Phase_1_Hardware_Architecture)
* **Focus:** Physical Construction, Power Distribution, and Kinematics.
* **Key Innovations:**
    * **Custom Power Distribution Hub:** A split-rail PCB design using "Solder Bridge Topology" to isolate noisy motor currents from sensitive sensor logic.
    * **Differential Drive Calibration:** Software-defined PWM trimming (`Left: 215` vs `Right: 255`) to correct inherent DC motor RPM mismatch.
    * **"Cool-Warm" Wiring Protocol:** A strict color-coded harnessing system to minimize debugging latency and cognitive load.

### 📂 [Phase 2: Firmware & Software Intelligence](./Project_A.R.E.S_Rover/Phase_2_Software_Architecture)
* **Focus:** Algorithmic Logic, Signal Processing, and Autonomy.
* **Key Innovations:**
    * **"Smart-Turn" Heuristic:** A look-and-compare navigation algorithm that executes precision 90° pivot turns towards the clearest path, eliminating stochastic spinning.
    * **Adaptive Signal Processing:** Boot-time auto-calibration for the Sound Sensor to filter ambient noise floors dynamically.
    * **Non-Blocking Core:** Utilization of asynchronous `millis()` timers to handle Telemetry, Sensing, and Actuation simultaneously.

---

## 🧠 Core Features & Logic

### 1. Hybrid Navigation System
The rover operates on a **Finite State Machine (FSM)** allowing instant mode switching:
* **Manual Mode:** Direct UART control via Bluetooth (Low Latency).
* **Autonomous Mode:** A deterministic decision tree for obstacle avoidance.
* **Stealth Mode:** A global interrupt that disables all HMI feedback (Lights/Sound) for silent operation.

### 2. Intelligent Signal Processing
* **Vision:** Servo-mounted Ultrasonic Radar providing a 180° Field of View (FoV).
* **Audio Interface:** The system calculates a `baseline` noise level on boot. Triggers are based on relative amplitude (`abs(Current - Baseline) > 50`) rather than fixed thresholds.
* **Surface Analysis:** IR Proximity sensors detect "Voids" or "Cliffs" (Active Low `< 200`), triggering an emergency stop.

### 3. State-Aware Illumination (Active Feedback)
The lighting system acts as a real-time debugging interface:
* **Forward:** Lights OFF (Power Save).
* **Reverse/Brake:** Backlights ON (Warning).
* **Cliff Detect:** Backlights Flash (Hazard).
* **Environment Sense:** Headlights activate automatically via LDR in low-light conditions.

---

## 🎮 Telemetry & Control Protocol
The system accepts UART commands (9600 Baud) via the HC-05 Bluetooth Module.

| Command Key | Function | Logic Description |
| :--- | :--- | :--- |
| **`F` / `B`** | Drive | Forward/Reverse with Backlight Logic |
| **`L` / `R`** | Turn | Pivot Turn (Zero Radius) |
| **`S`** | Stop | Emergency Halt + Brake Light |
| **`U`** | Autopilot | Toggle Autonomous AI Mode |
| **`D`** | Dance | Activate Choreographed Sequence |
| **`X`** | Stealth | Toggle Silent/Dark Mode |

---

## ⚙️ Technical Specifications

| Parameter | Specification |
| :--- | :--- |
| **Microcontroller** | ATmega328P (Arduino Uno R3) |
| **Propulsion** | 2x BO Gear Motors (DC 3-6V) |
| **Driver** | L298N Dual H-Bridge |
| **Power Source** | 2x 18650 Li-Ion Cells (7.4V Total) |
| **Vision Range** | 2cm - 400cm (HC-SR04) |
| **Comms Protocol** | UART (Bluetooth HC-05) |
| **Sensors** | Ultrasonic, IR Proximity, Sound (Mic), LDR |

---
*Algorithm, Logic & Firmware by **Sayon Ghosh** | CSE Undergraduate*
