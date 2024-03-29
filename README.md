# CAN Interface for ESP32

## Introduction

ESP32-Development-Boards contain powerful and inexpensive 32-bit microcontrollers and are well known for their low energy consumption. Due to their open design, the modules are well suited for (IoT) Internet of Things applications

CAN is a popular communication protocol in the automotive sector. It is a reliable and robust protocol which is designed for high-speed data transmission and real-time applications.
Although the microcontrollers have both CAN and Ethernet controllers integrated, there are currently no inexpensive boards available that provide an interface for the CAN bus.

Within this project, a circuit board is developed, which provides an interface between an ESP32 board and the CAN bus.


## Features

- Send and receive CAN Messages according to ISO11898-1
- Standard and extended frame format supported
- Various bus speeds supported
- Acts as a WLAN access point
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
- Connect to the CAN Bus either via SubD cable or via twisted pair of jumper cables (Pin Header: H (CAN High), L (CAN Low))
- Depending on the type of connection to the CAN bus (Subd or jumper cables) connect the pin headers via jumpers according to the following picture
  (A terminating resistor of 120 ohms is added between CAN High and CAN Low via JP1)
  
![grafik](https://github.com/AnRo301/CAN_Interface/assets/150276417/f7500303-a46a-465a-b11c-933e14cc1207)
- Install extension packages mentioned in 'Third Party Components' in VS Code
- Connect ESP32-S3 via USB-C Port to the pc
- Build and Upload Filesystem Image with PlatformIO
- Connect ESP32-S3 via USB-C COM Port to the pc
- Build and upload the Code with PlatformIO
  
![grafik](https://github.com/AnRo301/CAN_Interface/assets/150276417/e19d3fc5-d2b9-4a7d-94d6-edb0c335d542)

- Connect any device to the Wifi "CAN2WLAN" provided by the ESP32 acting as an access point
- Type in the following IP-Adresse in a browser: 192.168.4.1
- The following user interface should now appear:
  
![Benutzeroberfläche04](https://github.com/AnRo301/CAN_Interface/assets/150276417/685017a7-eac6-4eed-99bb-d03fd8f2448e)

 
Warning: Messages needs to be typed in in the right format. No detection of wrong/ unplausible input is implemented !





