/*
 * Project: IoT Phase 2 - WiFi Panic Alarm System
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: External GPIO Control (Active High Logic)
 * Key Concept: Current Source Topology & Web Interfacing
 * * * Engineering Logic:
 * - Unlike the internal LED (Active Low), external components like 
 * Buzzers and Red LEDs are connected in "Active High" configuration.
 * - Logic 1 (HIGH) -> Pin provides 3.3V -> Component ON (Source Current).
 * - Logic 0 (LOW)  -> Pin provides 0V   -> Component OFF.
 * * * API Endpoints:
 * - /led/on, /led/off   : Visual Warning Control
 * - /alarm/on, /alarm/off : Audio Siren Control
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// --- NETWORK CREDENTIALS ---
const char* ssid = "Sayon"; 
const char* password = "YOUR_PASSWORD"; // Update with your credentials

ESP8266WebServer server(80);

// Hardware Pin Definitions (Active High)
const int redLED = D1;    // GPIO 5
const int buzzer = D2;    // GPIO 4

void setup() {
  Serial.begin(115200);
  
  // Initialize GPIOs as Output (Source Configuration)
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Initial State: OFF (Active High: LOW = OFF)
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);

  // --- CONNECTION ESTABLISHMENT ---
  Serial.println("\n[System] Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[Network] System Online!");
  Serial.print("[Server] Control Panel: http://");
  Serial.println(WiFi.localIP());

  // --- ROUTE DEFINITIONS ---

  // Root Page
  server.on("/", []() {
    server.send(200, "text/plain", "ALARM SYSTEM READY. Endpoints: /led/on, /alarm/on");
  });

  // Visual Warning (LED)
  server.on("/led/on", []() {
    digitalWrite(redLED, HIGH); // Source Current -> ON
    server.send(200, "text/plain", "WARNING LIGHT: ACTIVATED");
    Serial.println("[CMD] Light ON");
  });
  
  server.on("/led/off", []() {
    digitalWrite(redLED, LOW);
    server.send(200, "text/plain", "WARNING LIGHT: DEACTIVATED");
    Serial.println("[CMD] Light OFF");
  });

  // Audio Warning (Buzzer)
  server.on("/alarm/on", []() {
    digitalWrite(buzzer, HIGH); // Source Current -> ON
    server.send(200, "text/plain", "SIREN: ACTIVATED 🚨");
    Serial.println("[CMD] Siren ON");
  });

  server.on("/alarm/off", []() {
    digitalWrite(buzzer, LOW);
    server.send(200, "text/plain", "SIREN: SILENCED");
    Serial.println("[CMD] Siren OFF");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}