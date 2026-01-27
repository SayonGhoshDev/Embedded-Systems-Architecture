/*
 * Project: Variable Frequency Strobe Light (Analog Signal Modulation)
 * Author: Sayon Ghosh (CSE Student)
 * Logic: Simulating Signal Modulation. 
 * - Potentiometer alters Voltage Amplitude (Brightness)
 * - Potentiometer alters Time Period / Frequency (Delay)
 */

const int signalPin = 11; // PWM Pin
const int potPin = A0;

void setup() {
  pinMode(signalPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin); // Read Input (0-1023)

  // Mapping Input to Amplitude (Brightness: 0-255)
  int brightness = map(potValue, 0, 1023, 0, 255);

  // Mapping Input to Frequency/Delay (Speed: 1000ms to 50ms)
  int speedDelay = map(potValue, 0, 1023, 1000, 50);
  
  // Signal HIGH (Pulse ON)
  analogWrite(signalPin, brightness);
  delay(speedDelay);

  // Signal LOW (Pulse OFF)
  analogWrite(signalPin, 0);
  delay(speedDelay);

  // Telemetry Log
  Serial.print("Signal Delay: ");
  Serial.print(speedDelay);
  Serial.println(" ms");
}