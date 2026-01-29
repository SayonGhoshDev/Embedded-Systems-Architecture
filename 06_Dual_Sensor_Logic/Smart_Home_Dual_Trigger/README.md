# 🚨 Dual Sensor Smart Home Automation

## 🎯 Objective
To design a robust Home Automation System that controls High-Voltage (220V AC) appliances using **Dual Hardware Interrupts**. The system features a hybrid trigger mechanism: **Touchless Gesture (IR)** for proximity control and **Audio Command (Clap)** for remote control, implementing advanced source identification logic.

## 🧠 Engineering Logic

### 1. Multi-Interrupt Architecture
* **Standard Approach:** Typically, loops check sensors sequentially. If one sensor takes time, the other is ignored.
* **Interrupt Approach:** This system uses **Pin 2 (INT0)** for IR and **Pin 3 (INT1)** for Sound. Both sensors have a direct "hotline" to the CPU. Whether you clap or wave, the processor reacts instantly, pausing the main loop to execute the toggle command.

### 2. Source Identification & Priority
* The code uses separate `volatile` flags (`irTriggered` vs `soundTriggered`) to identify exactly which sensor woke up the processor.
* **Conflict Management:** ISR functions include logic to prevent collision—if the IR is processing a signal, the Sound sensor is temporarily ignored (and vice-versa) to ensure system stability.

### 3. Safety & Debouncing
* **Cool-down Timer:** A `delay(1000)` is implemented after every toggle. This prevents the "Disco Light Effect" where withdrawing a hand might accidentally trigger the sensor multiple times.
* **Galvanic Isolation:** The Relay Module physically isolates the 5V Arduino logic from the 220V AC Mains, ensuring safety.

## 🛠️ Hardware Stack
* **Microcontroller:** Arduino Uno (ATmega328P)
* **Sensors:** * IR Sensor (TCRT5000) -> **Pin 2**
  * Sound Sensor (KY-037) -> **Pin 3**
* **Actuator:** 5V Relay Module (Active LOW) connected to AC Bulb.
* **Feedback:** Active Buzzer (Pin 11) & LED (Pin 9).

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
