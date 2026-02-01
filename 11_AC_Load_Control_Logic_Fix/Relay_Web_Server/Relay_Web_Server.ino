/*
 * Project: IoT Phase 2 - AC Load Control System
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: Web Server Interface (HTTP)
 * Key Concept: Logic Level Synchronization (3.3V vs 5V)
 * * * Engineering Logic:
 * - Standard 5V Relays often fail with 3.3V ESP8266 logic due to
 * insufficient potential difference (1.7V gap remains).
 * - FIX: Powered Relay VCC with 3.3V to match NodeMCU logic level.
 * - Logic 0 (LOW) -> Difference 3.3V -> Relay ON (Active Low).
 * - Logic 1 (HIGH) -> Difference 0V   -> Relay OFF.
 * * * API Endpoints:
 * - /on  : Activates AC Load (Light ON)
 * - /off : Deactivates AC Load (Light OFF)
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// --- NETWORK CREDENTIALS ---
const char* ssid = "YOUR_WIFI_NAME";     // Change this
const char* password = "YOUR_WIFI_PASSWORD"; // Change this

ESP8266WebServer server(80);

// Hardware Pin Definitions
// D6 (GPIO 12) connected to Relay IN pin
const int relayPin = D6; 

void setup() {
  Serial.begin(115200);
  
  // Initialize GPIO
  pinMode(relayPin, OUTPUT);
  
  // Initial State: OFF 
  // (For Active Low Relay running on 3.3V, HIGH keeps it OFF)
  digitalWrite(relayPin, HIGH);

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
    server.send(200, "text/plain", "N.E.X.U.S. RELAY SERVER ONLINE. Use /on or /off");
  });

  // Load Activation
  server.on("/on", []() {
    digitalWrite(relayPin, LOW); // Active Low Trigger -> ON
    server.send(200, "text/plain", "RELAY STATUS: ACTIVATED (Light ON) 💡");
    Serial.println("[CMD] Relay ON");
  });
  
  // Load Deactivation
  server.on("/off", []() {
    digitalWrite(relayPin, HIGH); // Potential Difference 0V -> OFF
    server.send(200, "text/plain", "RELAY STATUS: DEACTIVATED (Light OFF) 🌑");
    Serial.println("[CMD] Relay OFF");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}