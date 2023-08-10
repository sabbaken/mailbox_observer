#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <LoRa.h>

#define BOTtoken "xxx"
#define WIFI_SSID "xxx"
#define WIFI_PASSWORD "xxx"
#define CHAT_ID "xxx"

#define STATUS_CODE_MAILBOX_OPENED "o"
#define STATUS_CODE_OBSERVER_RESTARTED "r"
#define STATUS_CODE_ERROR_HALL_SENSOR_1 "eh1"

const int csPin = D8;        // LoRa radio chip select
const int resetPin = D3;     // LoRa radio reset
const int irqPin = D2;       // LoRa hardware interrupt

WiFiClientSecure wifiClient;
UniversalTelegramBot bot(BOTtoken, wifiClient);

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  // Ignore SSL/TLS certificate errors
  wifiClient.setInsecure();

  // Initialize LoRa with specific pins
  LoRa.setPins(csPin, resetPin, irqPin);

  // Start LoRa
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setCodingRate4(8);
  LoRa.setSpreadingFactor(12);
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if(packetSize) {
    String incoming = "";
    while(LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    Serial.println(incoming);

    if(incoming == STATUS_CODE_MAILBOX_OPENED) {
      bot.sendMessage(CHAT_ID, "Mailbox was opened!", "");
    }

    if(incoming.length() > 0) {
       bot.sendMessage(CHAT_ID, "Raw message: " + incoming, "");
    }
  }
}
