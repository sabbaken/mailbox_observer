#include <LoRa.h>

#define BUTTON_PIN 2

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  LoRa.begin(915E6);  // Change this to your desired frequency.
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    LoRa.beginPacket();
    LoRa.print("Button pressed");
    LoRa.endPacket();
    delay(1000);  // A delay to debounce the button.
  }
}
