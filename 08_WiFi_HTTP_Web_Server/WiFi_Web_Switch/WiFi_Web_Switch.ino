/*
 * Project: IoT Phase 2 - The Invisible Switch (Web Server)
 * Author: Sayon Ghosh (CSE Undergraduate Student)
 * Architecture: TCP/IP Client-Server Model over WiFi
 * Key Concept: HTTP Request Handling & Route Management
 * * Logic:
 * - NodeMCU acts as a Station (STA) connected to a Router/Hotspot.
 * - It hosts a local Web Server on Port 80.
 * - Listens for 'GET' requests from a Client (Browser).
 * - Executes Hardware Commands based on URL endpoints (/on, /off).
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// --- NETWORK CREDENTIALS ---
const char* ssid = "YOUR_WIFI_NAME";     // 2.4GHz Network Only
const char* password = "YOUR_WIFI_PASSWORD"; 

// Create Server Object on Port 80 (Standard HTTP)
ESP8266WebServer server(80);

// Hardware Pin (Internal LED)
const int ledPin = D4; 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Initial State: OFF (Active Low)

  // --- 1. CONNECTION ESTABLISHMENT ---
  Serial.println("\n[System] Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[Network] Connected!");
  Serial.print("[Server] Host IP: http://");
  Serial.println(WiFi.localIP()); // Prints the Local IP (e.g., 10.100.xx.xx)

  // --- 2. ROUTE DEFINITIONS (API Endpoints) ---
  
  // Root Page (http://ip/)
  server.on("/", []() {
    server.send(200, "text/plain", "NEXUS Core Online. Use /on or /off endpoints.");
  });

  // Turn ON Command
  server.on("/on", []() {
    digitalWrite(ledPin, LOW); // Active Low ON
    server.send(200, "text/plain", "STATUS: ACTIVE (Light ON)");
    Serial.println("Command Received: LED ON");
  });

  // Turn OFF Command
  server.on("/off", []() {
    digitalWrite(ledPin, HIGH); // Active Low OFF
    server.send(200, "text/plain", "STATUS: INACTIVE (Light OFF)");
    Serial.println("Command Received: LED OFF");
  });

  // --- 3. SERVER START ---
  server.begin();
  Serial.println("[Server] HTTP Listening on Port 80...");
}

void loop() {
  // Active Listening Mode
  server.handleClient();
}