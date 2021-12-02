#include "EspMQTTClient.h"

EspMQTTClient client(
  "Taekniskolinn",  // SSID
  "",               // SSID Password
  "192.168.1.100",  // MQTT Broker server ip
  "",               // MQTTUsername
  "",               // MQTTPassword
  "TestClient"      // Client name that uniquely identify your device
);

char * topic = "topic/test";

void setup() {}

void onConnectionEstablished() {

  client.subscribe(topic, [] (const String &payload)  {
    Serial.println(payload);
  });

  client.publish("mytopic/test", "This is a message");
}

void loop() {
  client.loop();
}
