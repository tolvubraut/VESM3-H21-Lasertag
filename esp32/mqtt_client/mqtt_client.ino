#include "EspMQTTClient.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Laser
#define LASER_TRIGGER 18

// LDR
#define LDR_PIN 2

// Gamestats
int bullets = 30; // Initial amount of bullets
int health = 100; // Initial amount of health
char screen_buffer_ln1[30];
char screen_buffer_ln2[30];

void pin_setup(void) {
  pinMode(LASER_TRIGGER, INPUT_PULLUP);
  pinMode(LDR_PIN, INPUT);
}

void display_setup(void) {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
  display.clearDisplay();
}

void display_renderText(char *text, uint8_t x, uint8_t y) {
  display.setCursor(x, y);
  display.println(text);
}

void display_render(void) {
  //Updates Screen
  sprintf(screen_buffer_ln1, "Bullets: [%d]", bullets);
  display_renderText(screen_buffer_ln1, 0, 0);
  sprintf(screen_buffer_ln2, "%Health: [%d]", health);
  display_renderText(screen_buffer_ln2, 0, 10);
  display.display();
  display.clearDisplay();
}

EspMQTTClient client(
  "SiminnE87DE1",
  "SV4PAYDUMX",
  "test.mosquitto.org",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  Serial.begin(115200);
  pin_setup();
  display_setup();
  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("dabdabdab6969/telemetry", [](const String & payload) {
    Serial.println(payload);
  });

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
  client.subscribe("dabdabdab6969/telemetry", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });

  // Publish a message to "mytopic/test"
  client.publish("dabdabdab6969/telemetry", "This is a message"); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions
  client.executeDelayed(5 * 1000, []() {
    client.publish("dabdabdab6969/telemetry", "This is a message sent 5 seconds later");
  });
}

void loop()
{
  client.loop();
  delay(250);
  //display_render();
  //bullets = bullets - 1;

  // LDR
  int lightLevel = analogRead(LDR_PIN);
  int laserTrigger = digitalRead(LASER_TRIGGER);

  // Trigger is being pressed
  if (laserTrigger == 0) {
    Serial.println("Trigger pressed");
  }

  // Laser receiving large amount of light
  // Use median to calculate avg light to get more precise results
  if (lightLevel > 3000) {
    Serial.println("Got hit");  
  }
}
