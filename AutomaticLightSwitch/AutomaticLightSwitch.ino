#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

#include "OTA.h"
unsigned long entry;

int sleepDuration = 20;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  ArduinoOTA.setHostname("Haashim Light Switch");
  setupServo();
  serverConnect();
  setupOTA();
  setupMQTT();
}

void loop() {
  ArduinoOTA.handle();
  client.loop();
  awake();


//  toggleTest();
}
