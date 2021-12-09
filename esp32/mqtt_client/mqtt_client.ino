#include "EspMQTTClient.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

//MQTT Variables
String DEVICE_ID = "1";
#define telemetry_topic "dabdabdab6969/telemetry"
#define reload_topic "dabdabdab6969/reload"
#define reset_topic "dabdabdab6969/reset"
int data_rate = 1000;
unsigned long last_data_send;

//Json
DynamicJsonDocument gameData(512);
char json_buffer[512];

// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int previous_bullets;
int previous_health;


// Laser
#define LASER_TRIGGER 18
#define LASER_DELAY 200 // Delay between each shot in MS
#define LASER_SHOOT_DURATION 150 // How long the laser will be shooting for 
#define LASER_PIN 16
unsigned long laser_lastchange;


// LDR
#define LDR_PIN 33
#define LDR_DELAY 500
unsigned long LDR_lastchange;
unsigned long mqtt_failsafe_timer;

// Light reader



// Readrate for sensors
#define SENSOR_readrate 10
unsigned long SENSOR_lastread = 0;
int lightLevel;
int laserTrigger;
 

// Gamestats
int bullets = 30; // Initial amount of bullets
int health = 100; // Initial amount of health
char screen_buffer_ln1[30];
char screen_buffer_ln2[30];
char screen_buffer_ln3[30];
char game_id[11]; // Used to differentiate different laser tag games

// Reset mechanic
int reset = 0;
unsigned long reset_timer;

EspMQTTClient client(
  "Taekniskolinn",
  "",
  "test.mosquitto.org",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "TestClientv32",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

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

void resets(void) {
  bullets = 30;
  health = 100;  
};

// Mean light
int normrn = 2000;
int spiketresh = 200;
const int DistTestAvarageCount = 100;
float dists[DistTestAvarageCount] = {};
int nextWrite = 0;
int readLight(int light){  

  dists[nextWrite] = light;
  nextWrite = (nextWrite + 1) % DistTestAvarageCount;

  int sum = 0;
  for(int i=0;i<DistTestAvarageCount;i++){
    sum += dists[i];
  }

  normrn =  sum / DistTestAvarageCount;
  return normrn;
}

void display_renderText(char *text, uint8_t x, uint8_t y) {
  display.setCursor(x, y);
  display.println(text);
};

void display_render(void) {
  //Updates Screen
  sprintf(screen_buffer_ln1, "Bullets: [%d]", bullets);
  display_renderText(screen_buffer_ln1, 0, 0);
  sprintf(screen_buffer_ln2, "%Health: [%d]", health);
  display_renderText(screen_buffer_ln2, 0, 10);
  if (bullets == 0) {
    sprintf(screen_buffer_ln3, "Reload");
    display_renderText(screen_buffer_ln3, 0, 20);
    
  } else {
    memset(screen_buffer_ln3, 0, sizeof(screen_buffer_ln3)); 
  }
  display.display();
  display.clearDisplay();
}

void screen_reset(void) {
  display.display();
  display.clearDisplay(); 
}

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
  //General payload
  //client.subscribe(telemetry_topic, [](const String & payload) {
    //Serial.println(payload);
  //});

  //Reload
  client.subscribe(reload_topic, [](const String & topic, const String & payload) {
    Serial.println(payload);
    if (payload == DEVICE_ID) {
      bullets = 30;
      memset(screen_buffer_ln3, 0, 30);
    };
  });

  // Reset
  client.subscribe(reset_topic, [](const String & topic, const String & payload) {
    reset = 1;
    Serial.println("Resetting");

  });

}

void loop()
{
  client.loop();
  if (millis() > reset_timer and reset == 0) {
     // LDR og Laser
    if (millis() > SENSOR_lastread + SENSOR_readrate) {
      lightLevel = analogRead(LDR_PIN);
      laserTrigger = digitalRead(LASER_TRIGGER);
      SENSOR_lastread = millis();
      Serial.println(lightLevel);
    };
    
  
    //Power to the laser
    if (millis() < laser_lastchange + LASER_SHOOT_DURATION and bullets != 0) {
      Serial.println("Shooting");  
      digitalWrite(LASER_PIN, HIGH);
      
    } else {
      digitalWrite(LASER_PIN, LOW);  
    };
    
    // If user shoots
    if (laserTrigger == 0) {
      if (millis() < laser_lastchange + LASER_DELAY) {
        // 
      } else if (millis() > laser_lastchange + LASER_DELAY and bullets > 0){
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
      if (millis() > last_data_send+data_rate){
        gameData["command"] = "info";
        gameData["health"] = health; 
        gameData["ammo"] = bullets;
        gameData["device"] = DEVICE_ID;
        serializeJson(gameData, json_buffer);
        client.publish(telemetry_topic, json_buffer);
        memset(json_buffer, 0, sizeof(json_buffer));
        last_data_send = millis();
      }
    }
  
    // Laser receiving large amount of light
    if (lightLevel > 4000) {
      if (millis() > LDR_lastchange + LDR_DELAY) {

        if (health > 0) {
          Serial.println("Got hit");
          health = health-25; 
          LDR_lastchange = millis();
        }
        if (health <= 0 or health == 0) {
          //Player died 
          if (millis() > mqtt_failsafe_timer){
            mqtt_failsafe_timer = millis()+5000;
            gameData["command"] = "reset";
            serializeJson(gameData, json_buffer);
            client.publish(telemetry_topic, json_buffer);
            memset(json_buffer, 0, sizeof(json_buffer));
          } 
        } 
        } else if (!millis() <= LDR_lastchange + LDR_DELAY) {
          // Received a shot too recently
          //grace period
      } 
    }
  } else if (reset == 1) {
    reset = 0;
    reset_timer = millis()+5000;
    screen_reset();
    if (health <= 0) {
      sprintf(screen_buffer_ln1, "You lost!");
      display_renderText(screen_buffer_ln1, 0, 0);  
    } else {
      sprintf(screen_buffer_ln1, "You won!");
      display_renderText(screen_buffer_ln1, 0, 0);  
    }
    sprintf(screen_buffer_ln2, "Resetting...");
    display_renderText(screen_buffer_ln2, 0, 10);
    display.display();
    display.clearDisplay();
    resets();
  }
}
