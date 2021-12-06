## Esp32D og LDR
Þarf sirka 5k resistor sem togar gildið upp í c.a. 3k, það kemst aðeins upp í 4k ef það er frekar bjart ljós á ldr eða laser. Svo er hægt að breyta breakpointini niður í 3.5-3.7k til að fá næmari trigger með laserinum


## MQTT|JSON söfn fyrir esp|arduino
[MQTT Safn](https://github.com/plapointe6/EspMQTTClient)

[JSON safn](https://github.com/arduino-libraries/Arduino_JSON)

## Varðandi ESP32 og LDR
Það er galli með summa pinna þegar er notað EspMQTTClient safnið
Nota pina nr 33 fyrir LDR