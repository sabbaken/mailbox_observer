# LoRa-Based Mailbox Alert with Telegram Notification
This project is an IoT application that alerts you via Telegram when your mailbox is opened. The system utilizes a Hall effect sensor and a magnet to detect when the mailbox is opened. The sensor is connected to an Arduino Pro Mini and a LoRa module to transmit a wireless signal. The receiver, a Wemos D1 Mini with a LoRa module, receives the signal and sends an alert to a specified Telegram chat.

## Hardware Requirements
- Arduino Pro Mini (3.3V version recommended for power saving)
- Wemos D1 Mini
- 2x LoRa Modules (compatible with Arduino and Wemos D1)
- Hall effect sensor
- Small magnet
- Battery
- Jumper wires and a breadboard (for prototyping)

## Software Requirements
Arduino IDE
LoRa Library by Sandeep Mistry
UniversalTelegramBot Library
Low-Power Library by Rocket Scream (for battery optimization)
System Description
The Hall effect sensor is attached to the mailbox door, and the magnet is attached to the mailbox itself. When the mailbox door is opened, the sensor detects the absence of the magnetic field and sends a signal to the Arduino Pro Mini.

The Arduino Pro Mini, which is in a power-saving sleep mode most of the time, wakes up and sends a message via the LoRa module. This message is received by the LoRa module attached to the Wemos D1 Mini. The Wemos D1, which is connected to the internet, sends an alert message to a specified Telegram chat.

Additionally, the system is designed to operate on a battery and includes power-saving features such as putting the Arduino to sleep when not in use and waking it up when the mailbox is opened. The system also sends low battery and lost connection alerts to your Telegram.

## Installation and Configuration

