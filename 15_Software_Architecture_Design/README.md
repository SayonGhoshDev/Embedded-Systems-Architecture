# 🧠 Advanced Software Architecture & Algorithmic Logic

## 📋 Executive Summary
This documentation details the **Software DNA** governing the Project A.R.E.S. and Project N.E.X.U.S. ecosystems. Unlike basic procedural programming, this architecture leverages **Event-Driven Design**, **Finite State Machines (FSM)**, and **Non-Blocking Multitasking** to ensure real-time responsiveness and system stability on the ESP8266/ATmega328P platforms.

---

## 🤖 1. Finite State Machine (FSM) Architecture
### 📉 The Problem: Spaghetti Code
Standard `if-else` logic becomes unmanageable in complex robotics. A robot cannot simultaneously "Scan" and "Drive" without conflicting instructions, leading to undefined behaviors (e.g., oscillating motors).

### 🛡️ The Solution: Deterministic State Logic
We implemented a **Finite State Machine (FSM)** to define discrete "Moods" or operating modes for the robot.
* **State Definitions:**
    * `STATE_IDLE`: System standby (Waiting for command).
    * `STATE_SCANNING`: Servo sweeps 0°-180° to map the environment.
    * `STATE_DECISION`: AI Logic computes the optimal path (Left vs Right).
    * `STATE_DRIVE`: PID-controlled motor movement.
* **Implementation:** Utilizing `switch...case` logic ensures the processor executes only **one specific behavior** at a time, eliminating logical conflicts and sensor noise jitter.

---

## ⏱️ 2. Non-Blocking Multitasking (Time-Slicing)
### ⚠️ The Risk: CPU Paralysis
The traditional `delay(1000)` function halts the entire CPU for 1 second. During this "Sleep Mode," the system becomes **blind and deaf**—unable to read sensors or accept emergency stop commands.

### 🔧 The Engineering Fix: `millis()` Concurrency
We replaced blocking delays with **Time-Division Multiplexing** using the internal hardware timer (`millis()`).
* **Logic:** `if (currentTime - previousTime >= interval) { execute(); }`
* **Result:** The processor checks sensors, updates LEDs, and drives motors effectively "simultaneously" by slicing tasks into microsecond-level execution blocks.
* **Benefit:** Achieves **Real-Time Responsiveness** essential for obstacle avoidance and safety protocols.

---

## ⚡ 3. Hardware Interrupts (ISR) vs Polling
### 🔄 The Polling Paradox
In a standard loop, the CPU wastes cycles constantly asking "Is the sensor triggered?". If the CPU is busy processing WiFi data, it might miss a fast-moving intruder (IR signal).

### 🚀 The "Event-Driven" Fix: Interrupt Service Routines
We utilized **Hardware Interrupts** (Pins D2/D3) to instantly pause the main loop and execute critical code.
* **Trigger:** Falling Edge detection (Voltage drop from HIGH to LOW).
* **Latency:** Microsecond-level response time.
* **Context:** Used for **Project N.E.X.U.S. Security System** (PIR/IR Sensors) to guarantee intrusion detection regardless of CPU load.

---

## 💾 4. Memory Management & Signal Processing
### 🧠 Optimized Data Types
* **`bool` (1-bit):** Used for State Flags (e.g., `isDoorOpen`) to minimize RAM usage.
* **`const` (Read-Only):** Hardware pin definitions are stored in Flash Memory (PROGMEM) instead of SRAM to prevent stack overflow.

### 📡 Signal Filtration (Debouncing & Hysteresis)
* **Debouncing:** Implemented software timers to ignore mechanical switch noise (millisecond-level voltage spikes).
* **Hysteresis (Schmidt Trigger Logic):**
    * **Logic:** Open door at `<10cm`, Close door at `>15cm`.
    * **Physics:** This **5cm Dead Band** prevents the servo motor from "chattering" or oscillating when an object hovers at the threshold distance.

---

## 📡 5. Communication Protocol: Virtual UART
### 🔗 The "SoftwareSerial" Bridge
Since the Hardware UART (Pins 0/1) is reserved for USB Debugging, we emulated a secondary Serial Port on GPIO pins using **Bit-Banging**.
* **Function:** Enables simultaneous communication with the PC (Serial Monitor) and the Bluetooth Module (HC-05).
* **Application:** Allows real-time telemetry data (Sensor distance, Motor speed) to be sent to the Android App while debugging the code logic.

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*

