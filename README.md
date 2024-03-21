# CAN Interface for ESP32

## Introduction

ESP32-Development-Boards contain powerful and inexpensive 32-bit microcontrollers and are well known for their low energy consumption. Due to their open design, the modules enable to connect network-based actuators and sensors.
Although the microcontrollers have both CAN and Ethernet controllers integrated, there are currently no low-cost boards available that have an interface for the Ethernet controller.

CAN is a popular communication protocol in the automotive sector. It is a reliable and robust protocol which is designed for high-speed data transmission and real-time applications.
Although the microcontrollers have both CAN and Ethernet controllers integrated, there are currently no inexpensive boards available that provide an interface for the CAN bus used in all vehicles.

Within the scope of this project, a circuit board is to be developed, which is an interface between an ESP32 board and the CAN bus.


## Features

- Send and receive CAN Messages according to ISO11898-1
- Standard and extended frame format supported
- Various bus speeds supported
- Acts as a wireless access point
- Received CAN messages are forwarded via web socket and can be viewed via a web interface on any device that is connected to the provided network
- Messages that are to be sent via the bus can be entered using the web interface and are transmitted via web socket to the microcontroller, which initiates the sending via CAN Bus

## Third Party Components
Hardware:
- esp32-s3-devkit-1
- USB-C cables
- SubD cable or twisted pair of jumper cables
- any device that supports wifi (computer/ tablet/ phone)

Software:
- Visual Studio Code
- Required Extension Packages:
  - PlatformIO IDE
  - Arduino
  - ESP-IDF
  
## How to run the project?
- Connect CAN Bus module to ESP32-S3 (pin labels must match)
![grafik](https://github.com/AnRo301/CAN_Interface/assets/150276417/86362c21-a6dc-4350-b065-2b70edaa49b3)
- Connect the CAN Bus either via SubD cable or via twisted pair of jumper cables (Pin Header: H (CAN High), L (CAN Low))
- Depending on the type of connection to the CAN bus (Subd or jumper cables) connect the pin headers via jumpers according to the following picture
  (A terminating resistor of 120 ohms is added between CAN High and CAN Low via JP1)
  
![grafik](https://github.com/AnRo301/CAN_Interface/assets/150276417/01a459c8-6b94-4047-8147-8d6eaf9117c7)

- Connect ESP32-S3 to the USB port, select the corresponding board and port
- Install extension packages mentioned in 'Third Party Components'
- Build and upload the Code with PlatformIO
- Connect any device to the Wifi "CAN2WLAN" provided by the ESP32 acting as an access points
- Type in the following IP-Adresse in a browser: 192.168.4.1
- The following user interface should now appear:
![Benutzeroberfläche03](https://github.com/AnRo301/CAN_Interface/assets/150276417/ddb95fc1-db53-44fe-9168-908b1346a2e3)

Warning: Only certain CAN speeds are possible: 25KBit/s, 50KBit/s, 100KBit/s, 125KBit/s, 250KBit/s, 500KBit/s, 800KBit/s, 1MBit/s

Warning: Messages needs to be typed in in the right format. No detection for wrong/ unplausible input is implemented !





