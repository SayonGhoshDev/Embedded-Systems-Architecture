# Embedded Systems Architecture & AIoT Integration 🚀

## 📜 Project Overview
This repository documents the development of scalable embedded software architectures, moving from **bare-metal AVR control** to **Cloud-Native IoT solutions**. The focus is not just on wiring components, but on writing optimized, non-blocking code logic, implementing communication protocols, and designing autonomous decision-making algorithms.

## 🛠️ Architecture Modules

### Phase 1: Core Signal Processing & Concurrency
* **Time-Division Multiplexing:** Replacing blocking `delay()` with `millis()` based State Machines for multitasking.
* **PWM & Timer Interrupts:** Precision control of servo actuators using duty-cycle manipulation.
* **Hardware Interrupts (ISR):** Implementing real-time event handling for security systems to minimize CPU polling overhead.

### Phase 2: Power Electronics & Protocol Implementation
* **Galvanic Isolation & AC Control:** Designing safe interfaces for High-Voltage (220V) appliance switching.
* **Single-Wire Protocol:** Decoding custom data streams from DHT sensors.
* **PCB Fabrication:** Transitioning from prototyping to permanent soldering standards.

### Phase 3: Autonomous Robotics & Control Systems
* **H-Bridge Physics:** Managing torque and back-EMF in DC motor drivers (L298N).
* **Sensor Fusion Algorithms:** Combining Ultrasonic and IR data for autonomous obstacle avoidance.
* **UART & Bluetooth Communication:** Implementing Master-Slave architecture for wireless telemetry and app-based control.

### Phase 4: Full-Stack IoT & Cloud Engineering
* **TCP/IP & Networking:** Configuring ESP8266 as Web Servers and Clients.
* **Cloud API Integration:** Handling HTTP Requests (GET/POST) and JSON parsing for global remote control.
* **Automation Logic:** Creating "If-This-Then-That" scenarios based on real-time sensor data.

## 🎓 Capstone Project
**AIoT Enabled Multi-Functional Service Robot:** A self-driving unit featuring obstacle avoidance, environmental monitoring, and cloud-synced telemetry with automated lighting control.

---
*Maintained by Sayon Ghosh | CSE Undergrad*
