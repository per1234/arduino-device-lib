#include <SoftwareSerial.h>
#include <TheThingsNetwork.h>

// Set your AppEUI and AppKey
const char *appEui = "0000000000000000";
const char *appKey = "00000000000000000000000000000000";

SoftwareSerial loraSerial(2, 3);
#define debugSerial Serial

TheThingsNetwork ttn(loraSerial, debugSerial, TTN_FP_MY915);

void setup() {
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);

  // Set callback for incoming messages
  ttn.onMessage(message);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}

void loop() {
  debugSerial.println("-- LOOP");

  // Send single byte to poll for incoming messages
  ttn.poll();

  delay(10000);
}

void message(const byte* payload, size_t length, port_t port) {
  debugSerial.println("-- MESSAGE");
  debugSerial.print("Received " + String(length) + " bytes on port " + String(port) + ":");

  for (int i = 0; i < length; i++) {
    debugSerial.print(" " + String(payload[i]));
  }

  debugSerial.println();
}
