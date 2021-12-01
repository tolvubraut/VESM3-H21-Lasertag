const uint8_t ldrPin = 0;
int lightlvl = 0;
void setup() {
 Serial.begin(115200);
}

void loop() {
  lightlvl = analogRead(ldrPin);
  if (lightlvl > 3500) {
    Serial.println("SHOT"); 
   }
  delay(33);
}
