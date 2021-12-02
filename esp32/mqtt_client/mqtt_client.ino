#include "EspMQTTClient.h"

EspMQTTClient client(
  "Taekniskolinn",  // SSID
  "",               // SSID Password
  "test.mosquitto.org",  // MQTT Broker server ip
  "",               // MQTTUsername
  "",               // MQTTPassword
  "TestClient"      // Client name that uniquely identify your device
);

const char* topic = "topic/test";

void setup() {}

void onConnectionEstablished() {

  client.subscribe(topic, [] (const String &payload)  {
    Serial.println(payload);
  });

  client.publish(topic, "This is a message");
}

void loop() {
  client.loop();
}
