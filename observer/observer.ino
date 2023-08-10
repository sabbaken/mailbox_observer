#include <ESP8266WiFi.h>
#include <LoRa.h>

#define STATUS_CODE_MAILBOX_OPENED "o"
#define STATUS_CODE_OBSERVER_RESTARTED "r"
#define STATUS_CODE_ERROR_HALL_SENSOR_1 "eh1"

const int csPin = D8;          // LoRa radio chip select
const int resetPin = D3;       // LoRa radio reset
const int irqPin = D2;         // LoRa hardware interrupt
const int hallSensor1Pin = D0;  // Assuming D4 for Hall effect sensor input, adjust as needed
const int ledPin = D4;         // Led pin

bool errorHallSensor1 = false;
bool mailboxOepenedFlag = false;

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(hallSensor1Pin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  // Initialize LoRa with specific pins
  LoRa.setPins(csPin, resetPin, irqPin);

  // Start LoRa
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setCodingRate4(8);
  LoRa.setSpreadingFactor(12);

  transmitStatus(STATUS_CODE_OBSERVER_RESTARTED);

  // delay(5000);

  int hallSensor1 = digitalRead(hallSensor1Pin);

  // Test if hall sensor can't detect magnet
  if (hallSensor1 == HIGH) {
    transmitStatus(STATUS_CODE_ERROR_HALL_SENSOR_1);
    errorHallSensor1 = true;
  }
}

void loop() {
  int hallSensor1 = digitalRead(hallSensor1Pin);
  
  if(!hallSensor1) {
    mailboxOepenedFlag = false;
  }

  if (!errorHallSensor1 && mailboxOepenedFlag == false && hallSensor1 == HIGH) {
    digitalWrite(ledPin, LOW);
    mailboxOepenedFlag = true;
    Serial.println("Mail box is opened");
    transmitStatus(STATUS_CODE_MAILBOX_OPENED);
    delay(1000);
    digitalWrite(ledPin, HIGH);
  }

  delay(10);
}

void transmitStatus(String status) {
  LoRa.beginPacket();
  LoRa.print(status);
  LoRa.endPacket();
}
