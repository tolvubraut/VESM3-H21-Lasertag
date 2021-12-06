/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-light-sensor
 */
 #include "EspMQTTClient.h"

 EspMQTTClient client(
  "SiminnE87DE1",
  "SV4PAYDUMX",
  "test.mosquitto.org",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void onConnectionEstablished()
{
 
}

#define LIGHT_SENSOR_PIN 33 // ESP32 pin GIOP36 (ADC0)

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

void loop() {
  client.loop();
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 40) {
    Serial.println(" => Dark");
  } else if (analogValue < 800) {
    Serial.println(" => Dim");
  } else if (analogValue < 2000) {
    Serial.println(" => Light");
  } else if (analogValue < 3200) {
    Serial.println(" => Bright");
  } else {
    Serial.println(" => Very bright");
  }
  delay(33);
}
