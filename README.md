# Vesm3 lokaverkefni - Sveinn og Bjartur

## Verkefnalýsing
Við bjuggum til Laser byssu sem er tengd við ESP32D og notar LDR ljósnæmi til að skynja hvenær laser er að beina á það.

Grunnvirkni leiksins er að hver er með skot og líf, þegar einhver tapar líf eða skot er það upplýsingar send yfir í Raspberry pi með MQTT.

Skotinn og lífið hjá leikmanni er sýnt á SSD1306 OLED skjá og þegar leikmaður deyr eða er ekki með skot er hann látinn vita gegnum skjáinn hvort hann tapaði/vann eða þarf að reloada. Til að reloada þarf leikmaður að fara að ammo station(raspberry pi) til að geta reloadað með RFID. Hver byssa er með sitt eigin unqiue rfid ID sem greinir hver var að byðja um skot. 

## Efnislisti
- ESP32D
- LDR sensor
- OLED SSD1306
- Raspberry pi 
- RC522 RFID
- Laser
- 10k viðnám
- bc547 transistor

## Kóði
[Laser byssa kóði](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/esp32/mqtt_client/mqtt_client.ino)

[Raspberry pi receiver/Ammo station](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/lasertag_raspberrypi.py)

[Server kóði fyrir vefappið](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/app.py)

## Hönnunarteikningar, Rafrásateikningar og tenglar
### Hönnunarteikningar
[Byssa - SVG](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/gun.svg)

[Kassi utan um ammo station - SVG](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/amohub.svg)

### Ljósmynd af upsetningu á brauðbretti.
![Brauðbretti](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/myndir_mynbond/grunuppsetning.jpg)

![Rafrásteikning-byssa](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/ByssuTenging.svg)
![Rafrásteikning-hub](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/amopickupTengingar.svg)


[Myndband af virkni](https://youtu.be/NeMznGbVOKM)


## Dagbók
### Tími 1
- Við byrjuðum að safna saman efnislista og hugsa hvað við þurftum að nota til fyrir verkefnið.
### Tími 2
- Við byrjuðum að kóða fyrir laserbyssuna(esp32d) og ammo kassan(raspberry pi) og náðum einföldu virkni. Bjuggum líka til einfalda síðu til að sýna gögnin
- Bjartur fór og fekk laser og tók hann í sundur til að sjá hvernig hann virkar og hvernig við mundum tengja hann við esp32d.
### Tími 3
- áÁhersla í þessum tíma var lögð í að ná almennilegri virkni með esp32d og laga alla galla sem komu fram. Bjartur teiknaði byssuna og ammo station fyrir laser skera.
### Tími 4
- En meiri tími í að laga galla i kóða og mjög mikill tími fór í samsettningu og þá sérstaklega lóðun. 

## Vandamál með verkefnið og Hönnunarákvarðanir.
- Aðal vandamál var að finna út hvernig við mundum ná laserinum til að virka og finna batterí sem gat knúið esp'inn í byssunum.  
- Kóðinn var smá vesen þar sem við þurftum að nota marga staðla til að þetta mundi allt virka. Json í esp, MQTT til að stjórna leikinum, POST til að senda upplýsingarnar í síðuna og ágætlega mikinn tími lagðir í að setja upp millis fyrir ESP þannig að esp32d mundi ekki missa út af einhverju skilaboðum t.d. Reset skipunum eða Reload skipunum.
- Upprunalega var planað að búa til 3d prenntaða byssu en vegna tímatakmarkana áháðum við að nota frekar laserskera sem er bæði fljótlegri hönnun og enn frekar fljótari prenntun. 


## Heimildir
Þegar það kemar að kóða var aðeins boilerplate notað hjá ESP MQTT safninu og allt annað var gert með notkun af docs hjá viðeigandi söfnunum.


### Aðal söfn
- [Json safn](https://arduinojson.org/)
- [ESP MQTT](https://www.arduino.cc/reference/en/libraries/espmqttclient/)
- [PAHO MQTT](https://pypi.org/project/paho-mqtt/)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)


# Skýrsla TODO
- Allur kóði, skrár og gögn. - Búið
- verkefnalýsing ásamt skýringarmyndum og efnislista. - Búið
- rafrásarteikning t.d með [Circuit Diagram](https://www.circuit-diagram.org/). - Búið
- hönnunarteikningar (til prentunar) 2d og eða 3d teikningar og model (.stl skráin), ef það á við. - Búið
- tengil á myndband (youtube) af notkun og virkni frumgerðar. - Búið
- tengla á kóðaskrár. - Búið
- ljósmyndir af samsettningu á IoT búnað og tilraunum. - Semi búið hægt að bæta fleirum myndum af tilraunum.
- helstu hönnunarákvarðanir, hvað var gert og heimildir. - allavega einhvað
