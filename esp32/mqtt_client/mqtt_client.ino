#include "EspMQTTClient.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//MQTT Variables
String DEVICE_ID = "2";
String device_topic = "dabdabdab6969/device/"+DEVICE_ID;
#define telemetry_topic "dabdabdab6969/telemetry"
#define reload_topic "dabdabdab6969/reload"


// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int previous_bullets;
int previous_health;

// Laser
#define LASER_TRIGGER 18
#define LASER_DELAY 500 // Delay between each shot in MS
#define LASER_SHOOT_DURATION 400 // How long the laser will be shooting for 
#define LASER_PIN 16
unsigned long laser_lastchange;


// LDR
#define LDR_PIN 33
#define LDR_DELAY 500
unsigned long LDR_lastchange;


// Readrate for sensors
#define SENSOR_readrate 33
unsigned long SENSOR_lastread = 0;
int lightLevel;
int laserTrigger;
 

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
  pinMode(LASER_PIN, OUTPUT);
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
  "Taekniskolinn",
  "",
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
  client.subscribe(telemetry_topic, [](const String & payload) {
    Serial.println(payload);
  });

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
  client.subscribe(reload_topic, [](const String & topic, const String & payload) {
    Serial.println(payload);
    if (payload == DEVICE_ID) {
      bullets = 30;
      memset(screen_buffer_ln3, 0, 30);
    };
  });

  // Publish a message to "mytopic/test"
  client.publish(telemetry_topic, "This is a message"); // You can activate the retain flag by setting the third parameter to true

}

void loop()
{
  client.loop();
   // LDR og Laser
  if (millis() > SENSOR_lastread + SENSOR_readrate) {
    lightLevel = analogRead(LDR_PIN);
    laserTrigger = digitalRead(LASER_TRIGGER);
    SENSOR_lastread = millis();
  };

  
  if (millis() < laser_lastchange + LASER_SHOOT_DURATION and bullets != 0) {
    Serial.println("Shooting");  
    // Put laser to high here
    
  };
  
  if (laserTrigger == 0) {
    if (millis() < laser_lastchange + LASER_DELAY) {
      // 
      if (bullets == 0) {
        sprintf(screen_buffer_ln3, "Reload");
        display_renderText(screen_buffer_ln3, 0, 20);
      } 
    } else if (millis() > laser_lastchange + LASER_DELAY){
      //Shoot
      laser_lastchange = millis();
      bullets = bullets -1;
    }
  };

  
  // Refresh screen when user fires the laser or looses health
  if (previous_bullets != bullets or previous_health != health){
    display_render();
    previous_bullets = bullets;
    previous_health = health;
  }

  // Laser receiving large amount of light
  if (lightLevel > 4000) {
    if (millis() > LDR_lastchange + LDR_DELAY) {
      Serial.println("Got hit");
      if (health == 0) {
        //Player died 
          sprintf(screen_buffer_ln3, "U dEd");
          display_renderText(screen_buffer_ln3, 0, 20);
        //Send with MQTT and inform other player that this player has died.
        //Also restart the game and reset all game variables after x time
      } else if (!millis() <= LDR_lastchange + LDR_DELAY) {
        // Received a shot too recently
        health = health-10; 
        LDR_lastchange = millis();
        client.publish(device_topic, "I took damage");
      } 
    } 
  }
}
