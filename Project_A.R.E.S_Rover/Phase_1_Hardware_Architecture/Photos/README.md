# 🦾 Project A.R.E.S. (Autonomous Robotic Exploration System) - Phase 1

## 📋 Executive Summary
**Project A.R.E.S.** represents a tactical initiative to engineer a scalable, autonomous rover platform capable of environmental sensing and remote telemetry. **Phase 1** focuses exclusively on the **Electro-Mechanical Architecture**, establishing a robust power distribution network, chassis kinematics, and logic-level integration. This document details the physical construction, wiring topology, and initial calibration of the rover's core subsystems.

---

## ⚡ 1. Power Distribution Matrix (Custom PCB)
### 📉 The Problem: Voltage Instability & Cable Clutter
Standard breadboard prototyping introduces loose connections and high resistance, leading to voltage drops (Brown-outs) when the Servo and Sonar sensors operate simultaneously with DC Motors.

### 🛡️ The Solution: High-Amperage Solder Bridge Topology
We engineered a **Custom Power Hub** using a General Purpose PCB to serve as the rover's central energy nervous system.
* **Architecture:** Split-Rail Design dividing **+5V (VCC)** and **Ground (GND)** into dedicated parallel buses.
* **Fabrication Physics:** Utilized the **"Solder Bridge" technique**, creating solid tin-lead conduits between header pins. This ensures:
    * **Low Impedance:** Minimal resistance for high-current delivery.
    * **Mechanical Rigidity:** Immune to vibrations during rover movement.
* **Integration:** Acts as the central interface for the Servo, Bluetooth Module, and Ultrasonic Sensor, isolating sensor power from the noisy L298N driver rail.

---

## ⚙️ 2. Chassis Kinematics & Motor Calibration
### ⚠️ The Risk: RPM Mismatch & Drift
Due to manufacturing tolerances in DC Gear Motors, identical voltage inputs ($V_{in}$) result in unequal Rotational Speed ($\omega$), causing the rover to drift significantly from a straight trajectory.

### 🔧 The Engineering Fix: Software-Defined PWM Trimming
Instead of mechanical dampening, we implemented a **Differential Drive Logic** at the firmware level (Calibration Phase).
* **Base Logic:** Right Motor requires higher torque actuation ($PWM = 255$) compared to the Left Motor.
* **Calibration Vector:** The Left Motor is logically throttled ($PWM \approx 215$) to synchronize the linear velocity ($v$) of both wheels.
* **Result:** Achieved stable rectilinear motion essential for future PID control implementation.

---

## 📡 3. Sensor Fusion & Signal Integrity
### 🌈 Wiring Topology: The "Cool-Warm" Protocol
To eliminate debugging latency, a strict **Color-Coded Harness System** was implemented:
* **Power Domain:** Red (VCC) / Black (GND).
* **Left Logic (Cool Colors):** White (Enable), Green/Blue (Direction).
* **Right Logic (Warm Colors):** Yellow (Enable), Orange/Brown (Direction).
* **Physics:** Reduces "Cognitive Load" during circuit analysis and minimizes the risk of reverse-polarity shorts.

### 🛡️ Dielectric Insulation (Stealth Mounting)
The **HC-05 Bluetooth Module** lacks mounting holes and poses a short-circuit risk if it touches the chassis or other components.
* **Technique:** Applied a **Dielectric Polymer Wrap (Electrical Tape)** to insulate the PCB backplane.
* **Mounting:** Secured via a tension-based elastic retention system (Rubber Band Hack) for shock absorption and easy modular replacement.

---

## 👁️ 4. Active Vision System (The Head)
### 🦕 Servo-Actuated Radar
* **Actuator:** SG90 Micro Servo acting as the "Neck," providing 180° Degree of Freedom (DoF).
* **Transducer:** HC-SR04 Ultrasonic Sensor mounted as the "Eyes."
* **Signal Extension:** Implemented a **Daisy-Chain Jumper Extension** with stress-relief taping to prevent signal wire tension during head rotation ranges ($0^\circ \leftrightarrow 180^\circ$).

---

## 🚀 5. Architectural Roadmap (Upcoming Modules)
The following subsystems are scheduled for integration in **Phase 2 & 3**:

| Subsystem | Component | Function |
| :--- | :--- | :--- |
| **Power Management** | **TP4056 Type-C** | Onboard Li-Ion Charging Protocol with Protection |
| **Night Vision** | **High-Power LEDs** | Headlights (White) & Taillights (Red) |
| **Environment Sense** | **LDR Module** | Automatic Light Detection & Activation |
| **Audio Processing** | **KY-037 Sensor** | Clap/Voice Command Recognition |
| **Line/Edge Tracking** | **IR Proximity** | Surface Detection & Cliff Avoidance |
| **HMI Feedback** | **Active Buzzer** | System Status Beeps & Alarm Signals |

---
*Concept, Architecture & Firmware by **Sayon Ghosh** | CSE Undergraduate*
