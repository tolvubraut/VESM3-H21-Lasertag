# vesm3_lokaverkefni

## Verkefnalýsing
Við bjuggum til Laser byssu sem er tengd við ESP32D og notar LDR ljósnæmi til að skynja hvenær laser er að beina á það.

Grunnvirkni leiksins er að hver er með skot og líf, þegar einhver tapar líf eða skot er það upplýsingar send yfir í Raspberry pi með MQTT.

Raspberry pi mundi svo senda POST request yfir í síðunna sem mun svo geyma það upplýsingar. Vegna of litlum tíma náðist það ekki að útfærast.

Skotinn og lífið hjá leikmanni er sýnt á SSD1306 OLED skjá og þegar leikmaður deyr eða er ekki með skot er hann látinn vita gegnum skjáinn hvort hann tapaði/vann eða þarf að reloada. Til að reloada þarf leikmaður að fara að ammo station(raspberry pi) til að geta reloadað með RFID. Hver byssa er með sitt eigin unqiue rfid ID sem greinir hver var að byðja um skot. 

## Efnislisti
- ESP32D
- LDR sensor
- OLED SSD1306
- Raspberry pi 
- RC522 RFID
- Laser

## Kóði
[Laser byssa kóði](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/esp32/mqtt_client/mqtt_client.ino)

[Raspberry pi receiver/Ammo station](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/lasertag_raspberrypi.py)

[Server kóði fyrir vefappið](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/app.py)

## Hönnunarteikningar, Rafrásateikningar og tenglar
### Hönnunarteikningar
[Byssa - SVG](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/gun.svg)

[Kassi utan um ammo station - SVG](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/amohub.svg)

### Síða
[Síða notuð til að sýna gögn](https://flask-scoreboard.herokuapp.com/)

### Ljósmynd af upsetningu á brauðbretti.
![Brauðbretti](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/myndir_mynbond/grunuppsetning.jpg)

[Rafrásteikning]()

## Dagbók
### Tími 1
- Við byrjuðum að safna saman efnislista og hugsa hvað við þurftum að nota til fyrir verkefnið.
### Tími 2
- Við byrjuðum að kóða fyrir laserbyssuna(esp32d) og ammo kassan(raspberry pi) og náðum einföldu virkni. Bjuggum líka til einfalda síðu til að sýna gögnin
- Bjartur fór og fekk laser og tók hann í sundur til að sjá hvernig hann virkar og hvernig við mundum tengja hann við esp32d.
### Tími 3
- áhersla í þessum tíma var lögð í að ná almennilegri virkni með esp32d og laga alla galla sem komu fram. 
### Tími 4
- En meiri tími í að laga galla og lóða allt saman.

## Vandamál með verkefnið og Hönnunarákvarðanir.
- Aðal vandamál var að finna út hvernig við mundum ná laserinum til að virka og með hvaða batterí við mundum þurfa til að þetta mundi virka, Kóðinn var líka smá vesenn þar sem við þurftum að nota marga staðla til að þetta mundi allt virka. Json í esp, MQTT til að stjórna leikinum, POST til að senda upplýsingarnar í síðuna og ágætlega mikinn tími lagðir í að setja upp millis fyrir ESP þannig að esp32d mundi ekki missa út af einhverju skilaboðum t.d. Reset skipunum eða Reload skipunum.

# Skýrsla TODO
- Allur kóði, skrár og gögn. - Búið
- verkefnalýsing ásamt skýringarmyndum og efnislista. - Vantar
- rafrásarteikning t.d með [Circuit Diagram](https://www.circuit-diagram.org/). - Vantar
- hönnunarteikningar (til prentunar) 2d og eða 3d teikningar og model (.stl skráin), ef það á við. - Búið
- tengil á myndband (youtube) af notkun og virkni frumgerðar. - Vantar
- tengla á kóðaskrár. - Búið
- ljósmyndir af samsettningu á IoT búnað og tilraunum. - Semi búið
- helstu hönnunarákvarðanir, hvað var gert og heimildir. - Vantar
