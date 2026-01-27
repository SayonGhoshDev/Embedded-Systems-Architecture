# Synchronized Electro-Mechanical Actuation System 🦾

## 📜 Overview
This project implements real-time synchronization between a mechanical actuator (Servo Motor) and an electrical indicator (LED). It focuses on **Data Normalization**, converting raw sensor data into multiple output formats to drive distinct hardware simultaneously without lag.

## ⚙️ Logic Architecture
* **Data Normalization:** Converts raw 10-bit Analog signals into:
  * **Mechanical Vector:** 0° to 180° for the Servo shaft.
  * **Electrical Scalar:** 0 to 255 (PWM) for LED brightness.
* **Sync Logic:** Ensures the visual indicator (LED) matches the mechanical state (Motor Position) in real-time.
* **Latency Handling:** Includes a stabilization delay (`15ms`) to account for the servo gearbox's physical slew rate.

## 🛠️ Hardware Requirements
* SG90 Micro Servo (Pin 11)
* LED Monitor (Pin 6)
* Potentiometer (Pin A0)
* Library: `<Servo.h>`

## 📊 Application
Used in robotic arms where visual feedback (intensity) indicates the torque or angle of joints.
