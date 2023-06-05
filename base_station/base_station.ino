#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>
#include <LoRa.h>

#define BOTtoken "your_bot_token"  // Your Bot's token obtained from BotFather
#define WIFI_SSID "your_SSID"      // Your WiFi SSID
#define WIFI_PASSWORD "your_PASSWORD"  // Your WiFi password

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  LoRa.begin(915E6);  // Change this to your desired frequency.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = LoRa.readString();
    if (receivedMessage == "Button pressed") {
      String chat_id = "your_chat_id";
      bot.sendMessage(chat_id, "Button pressed", "");
    }
  }
}
