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
int previous_bullets;
int previous_health;

// Laser
#define LASER_TRIGGER 18
#define LASER_DELAY 50 // Delay between each shot in MS
unsigned long laser_time;


// LDR
#define LDR_PIN 33

// Gamestats
#define ID 0;
int bullets = 30; // Initial amount of bullets
int health = 100; // Initial amount of health
char screen_buffer_ln1[30];
char screen_buffer_ln2[30];
char screen_buffer_ln3[30];

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
  "TestClientv32",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  Serial.begin(115200);
  pin_setup();
  display_setup();
  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
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
  client.subscribe("dabdabdab6969/reload", [](const String & topic, const String & payload) {
    Serial.println(payload);
    if (payload == "0") {
      bullets = 30;
      memset(screen_buffer_ln3, 0, 30);
    };
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
  delay(33);
  // Replace delay with a set of millis() to avoid missed inputs
  
  // Refresh screen when user fires the laser or looses health
  if (previous_bullets != bullets or previous_health != health){
    display_render();
    previous_bullets = bullets;
    previous_health = health;
  }

  // LDR
  int lightLevel = analogRead(LDR_PIN);
  int laserTrigger = digitalRead(LASER_TRIGGER);

  // Trigger is being pressed
  if (laserTrigger == 0) {
    Serial.println("Trigger pressed");
    bullets = bullets -1;
    // Tell user to reload
    if (bullets <= 0) {
      sprintf(screen_buffer_ln3, "Reload");
      display_renderText(screen_buffer_ln3, 0, 20);
    }  else {
      
    }
  }
  // Laser receiving large amount of light
  // Use median to calculate avg light to get more precise results
  //Serial.println(lightLevel);
  if (lightLevel > 3000) {
    Serial.println("Got hit");
    health = health-10;  

    if (health <= 0) {
      //Player died  
    }
  }
}
