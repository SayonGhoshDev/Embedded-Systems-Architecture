# Analog Signal Modulation & Variable Strobe Logic 🎛️

## 📜 Overview
This module demonstrates how to modulate a digital output signal's **Amplitude (Brightness)** and **Frequency (Time Period)** simultaneously using a single Analog Input source. It simulates basic signal processing logic often used in industrial indicators and communication beacons.

## ⚙️ Logic Architecture
* **Input Acquisition:** Reads 10-bit ADC data (0-1023) from a Potentiometer.
* **Signal Mapping:**
  * **Amplitude Control:** Maps input to 8-bit PWM duty cycle (0-255).
  * **Frequency Control:** Maps input to time delay values (50ms - 1000ms).
* **Execution:** Generates a variable-frequency strobe effect where speed and intensity are inversely or directly proportional to user input.

## 🛠️ Hardware Requirements
* Arduino Uno (ATmega328P)
* LED / Signal Light (Pin 11 - PWM)
* Potentiometer (Pin A0)

## 💻 Key Algorithm
```cpp
// Mapping Logic
int brightness = map(potValue, 0, 1023, 0, 255);   // Amplitude
int speedDelay = map(potValue, 0, 1023, 1000, 50); // Frequency
