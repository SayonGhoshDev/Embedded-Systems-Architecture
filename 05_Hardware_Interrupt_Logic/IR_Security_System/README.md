# 🚨 Hardware Interrupt Security System

## 🎯 Objective
To design a high-response security alarm system using **Infrared (IR) Sensors** and **Hardware Interrupts (ISR)**. Unlike standard looping methods, this system puts the processor in a passive monitoring state and only triggers the alarm instantly when an external hardware event occurs.

## 🧠 Engineering Logic

### 1. Polling vs. Interrupts
* **Polling (The Old Way):** In standard `if-else` logic, the CPU wastes cycles constantly asking "Is the thief here?". If the CPU is busy with a `delay()`, it might miss a fast-moving object.
* **Interrupts (The Professional Way):** This code uses **Hardware Interrupts (ISR)** on **Pin 2**. The CPU is free to do other tasks. When the sensor detects an intruder (Signal Falling Edge), it forces the processor to pause everything and execute the alarm function immediately.

### 2. Volatile Memory (`volatile`)
* Since the `detectionFound` variable is modified inside an ISR (which happens outside the main flow) and read by the main loop, it is declared as `volatile`.
* This tells the compiler **not to cache** the variable, ensuring the main loop always reads the freshest value from RAM.

## 🛠️ Hardware Stack
* **Microcontroller:** Arduino Uno (ATmega328P)
* **Sensor:** IR Obstacle Sensor (TCRT5000 Module) connected to **Pin 2** (Interrupt Pin).
* **Output:** Active Buzzer (Pin 9) & Status LED (Pin 10).

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
