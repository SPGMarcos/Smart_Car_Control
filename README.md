# SmartCarControl
🚗 Wi-Fi Controlled Robotic Car

ESP8266 (AP Mode) + Arduino + Real-Time Web Joystick


📌 Overview
This project consists of a fully functional Wi-Fi controlled robotic vehicle built using:
ESP-01 (ESP8266) operating in Access Point mode


Arduino Uno for motion control


H-Bridge motor driver


Servo motor for steering


Custom-built mechanical structure


Real-time web interface with responsive joystick


The system creates its own Wi-Fi network, hosts a web server, and allows real-time bidirectional control of traction and steering without the need for external routers or MQTT brokers.


🎯 Project Objective
The goal was to design a modular embedded system capable of:
Hosting its own wireless network


Providing a responsive web control interface


Processing real-time movement commands


Managing dual-axis control (traction + steering)


Implementing a lightweight serial communication protocol between microcontrollers


Integrating mechanical, electronic, and firmware layers


🧠 System Architecture
User (Smartphone / PC)
         ↓
  Wi-Fi Network (AP Mode)
         ↓
      ESP-01
  (Embedded Web Server)
         ↓
  Serial Communication
         ↓
     Arduino Uno
         ↓
  H-Bridge + Servo
         ↓
      Motion


🔹 Responsibility Separation
Component
Responsibility
ESP-01
Creates Wi-Fi AP + Hosts Web Server
Web Interface
Generates movement commands
ESP-01
Sends commands via Serial
Arduino
Parses and executes commands
H-Bridge
Controls motor direction
Servo
Controls steering angle

This separation improves modularity and scalability.

🔌 Mechanical Engineering & Physical Construction
The vehicle was physically designed and assembled with a modular architecture.
Structure Highlights:
Rigid base chassis


Rear traction system


Front steering system with servo linkage


Dedicated battery compartment


Removable upper body for maintenance


Organized internal wiring layout


Design Considerations:
Ease of maintenance


Modular expansion (camera, sensors, telemetry)


Electrical separation between control and power


Structural stability during motion


The physical build demonstrates integration between mechanical design and embedded systems.


⚙️ Firmware – Arduino (Motion Controller)
The Arduino is responsible for:
Receiving serial commands from ESP-01


Parsing dual-command format


Controlling H-Bridge pins


Controlling servo positioning






Command Parsing Logic
Commands follow this structure:
TRACTION,DIRECTION
Example:
F,E
The firmware separates commands using:
int pos = comando.indexOf(',');
Each command is executed independently, allowing simultaneous steering and movement.

📡 Firmware – ESP8266 (Web Server & Network Layer)
The ESP-01 performs:
Wi-Fi Access Point creation


HTTP server hosting


Real-time command transmission


Interface delivery via PROGMEM


Network Configuration
SSID: CarrinhoRC
Password: 12345678
IP Address: 192.168.4.1
The HTML interface is stored in flash memory using PROGMEM, optimizing RAM usage.


🌐 Web Interface – Responsive Joystick
The interface was built using:
HTML5


Canvas API


Touch events


JavaScript vector calculation


Fetch API for asynchronous requests


Control Logic
Y-axis controls traction (F/R/P)


X-axis controls steering (E/D/C)


15px dead zone to prevent noise


Command transmission only when state changes


Automatic reset to neutral on release


This reduces serial traffic and improves stability.


🔄 Communication Protocol
Code
Function
F
Forward
R
Reverse
P
Stop
E
Left
D
Right
C
Center



Example combinations:
F,E → Forward Left


F,D → Forward Right


R,C → Reverse Straight


P,C → Neutral



🛠 Technologies Used
Hardware
ESP8266 (ESP-01)


Arduino Uno


H-Bridge Motor Driver


Servo Motor


DC Motor


5V Power Supply


Software
C++ (Arduino)


ESP8266WebServer


SoftwareSerial


HTML5 + JavaScript


Embedded Serial Protocol




🔐 Engineering Improvements Implemented
Simultaneous dual-axis control


Dead zone filtering


Reduced redundant command transmission


Modular firmware separation


AP-based independence (no router required)


Structured communication protocol


📷 Project Media
Add:
Image of disassembled structure


Image of electronics mounted


Screenshot of web interface


Demonstration video link


📈 Future Improvements
PWM speed control


WebSocket real-time communication


Battery telemetry


ESP32 unified architecture


Onboard camera streaming


Mobile app interface



👨‍💻 Author
Marcos Gabriel Ferreira Miranda

IoT & Embedded Systems Developer

Belo Horizonte - MG

