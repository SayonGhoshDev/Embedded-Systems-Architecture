# 🌐 WiFi HTTP Web Server Switch

## 🎯 Objective
To transform the standalone microcontroller into a network-attached **Web Server** capable of handling Hypertext Transfer Protocol (HTTP) requests. This project bridges the gap between hardware (GPIO) and software (Web Browser), creating the foundational architecture for the **Project N.E.X.U.S.** Smart Home Ecosystem.

## 🧠 Engineering Logic

### 1. Client-Server Architecture
The system operates on a localized TCP/IP model:
* **The Server (NodeMCU):** Hosts the control logic and listens on **Port 80**.
* **The Client (Smartphone/Laptop):** Sends standard `GET` requests via a Web Browser.
* **The Protocol:** HTTP (Hypertext Transfer Protocol). *Note: ESP8266 supports HTTP, not HTTPS.*

### 2. Route Management
The server does not serve static HTML files; instead, it uses **API Endpoints** (Routes) to trigger functions:
* **Route `/`:** Returns system health status.
* **Route `/on`:** Triggers the GPIO Sink (LOW) -> **LED ON**.
* **Route `/off`:** Triggers the GPIO Source (HIGH) -> **LED OFF**.

### 3. Network Constraints
* **Frequency:** The ESP8266 operates strictly on the **2.4 GHz** band (Higher Range, Lower Speed), which is ideal for IoT command packets.
* **Local IP:** The device is assigned a Dynamic IP via DHCP (e.g., `10.100.xx.xx` or `192.168.xx.xx`) visible only within the Local Area Network (LAN).

## 🛠️ Hardware Stack
* **Microcontroller:** NodeMCU v3 (ESP8266)
* **Connectivity:** WiFi 802.11 b/g/n (2.4 GHz)
* **Client Interface:** Google Chrome / Any Web Browser

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
