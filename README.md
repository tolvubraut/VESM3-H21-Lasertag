<!-- setjið kóðann efst í README skrána. Í html skrá fer <styles> í <head> og <div> efst í <body> -->
<style>
    body {
        margin-top:5em;
    }
    .headwrapper {
        position:fixed ;
        top:0;
        left:0;
        right:0;
        height: 3.5em;
        background-color: #fff; 
        border: 0;   
        box-shadow: 0 0 1em #ddd;
        z-index:99;
    }             
    .headmenu {
        width:100%;
        padding: 0 1em;
    } 
    .logo  {
        display: flex;
        align-content: center;
    }  
    .logo a{
        text-decoration: none;
    }
    .logo img{
        width: 2.5em;
        height: 3.5em;
    }
    .logotxt {   
        color: #0B3E7A;
        font-family: sans-serif;
        text-decoration: none;
        text-align: left;
        padding-top:1.3em;
    }
</style>
<div class="headwrapper">
    <div class="headmenu"> 
        <div class="logo"> 
            <a href="https://tolvubraut.github.io/" title="Tölvubraut Tækniskólans"><img src="tskoli-logo.svg" title="Aftur á vef tölvubrautar"></a>  
            <a href="https://tolvubraut.github.io/" title="Tölvubraut Tækniskólans" class="logotxt">TÖLVUBRAUT - <em>stúdentspróf</em></a>   
        </div>
    </div>
</div> 

# Vesm3 lokaverkefni - Sveinn og Bjartur

## Verkefnalýsing

Við bjuggum til prototípu af lasertag leik þar sem spilarar hafa byssu með takmörkunum skotum og ákveði mörg skot sem þeir geta tekið áður en þeir tapa leiknum.

Grunnvirknin leiksins er sú að þegar byssa annað hvort skýtur eða er skotinn sendir hún uppfærðar upplýsingar um stöðu sína, i gegnum MQTT, á raspberry sem sér svo um að segja byssunum þegar leiknum er lokið og hvor vann eða tapaði. Raspberry'inn er líka skota pickup; ef maður notar öll skotinn sín þarf maður að fara að ná í fleiri skot. Það er gert með því að skanna byssuna með rfid'i sem er innbyggt í henni og þá sendir raspberryinn skilaboð til viðeigandi byssu um að endurstilla skotafjöldann. 

Skotinn og lífið leikmanna er sýnt á SSD1306 OLED skjá og þegar leikmaður deyr eða er ekki með skot er hann látinn vita gegnum skjáinn, hvort hann tapaði/vann eða þarf að reloada.


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

### upsetningu á brauðbretti.
![Brauðbretti](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/myndir_mynbond/grunuppsetning.jpg)

### Loka uppsetning byssu
![byssa](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/byssa-uppsettnitg.jpg)

### Rafrásar teikningar
![Rafrásteikning-byssa](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/ByssuTenging.svg)
![Rafrásteikning-hub](https://github.com/sveinnoli/vesm3_lokaverkefni/blob/main/amopickupTengingar.svg)


### [Myndband af virkni](https://youtu.be/NeMznGbVOKM)


## Dagbók
### Tími 1
- Við byrjuðum að safna saman efnislista og hugsa hvað við þurftum að nota til fyrir verkefnið.
### Tími 2
- Við byrjuðum að kóða fyrir laserbyssuna(esp32d) og ammo kassan(raspberry pi) og náðum einföldu virkni. Bjuggum líka til einfalda síðu til að sýna gögnin
- Bjartur fór og fékk laser og tók hann í sundur til að sjá hvernig hann virkar og hvernig við mundum tengja hann við esp32d.
### Tími 3
- Áhersla í þessum tíma var lögð í að ná almennilegri virkni með esp32d og laga alla galla sem komu fram. Bjartur teiknaði byssuna og ammo station fyrir laser skera.
### Tími 4
- En meiri tími í að laga galla i kóða og mjög mikill tími fór í samsetningu og þá sérstaklega lóðun. 

## Vandamál með verkefnið og Hönnunarákvarðanir.
- stærstu vandamálin sem við lentum í voru að fá laser og hakka hann í laser byssu og hvernig við gætum skynjað laser hit. 
- Kóðinn var mikið vesen þar sem við þurftum að nota marga staðla til að þetta mundi allt virka. Json í esp, MQTT til að stjórna leiknum, POST til að senda upplýsingarnar í síðuna og mikill tími var lagður í að setja upp millis fyrir ESP þannig að hann myndi ekki missa af einhverju skilaboðum t.d. Reset skipunum eða Reload skipunum.
- Upprunalega var planað að búa til 3d prentaða byssu en vegna tímatakmarkanna áháðum við að nota frekar laserskera sem er bæði fljótlegri hönnun og enn frekar fljótari prentun. 


## Heimildir
Þegar það kemur að kóða var aðeins boilerplate notað hjá ESP MQTT safninu og allt annað var gert með notkun af docs hjá viðeigandi söfnunum.


### Aðal söfn
- [Json safn](https://arduinojson.org/)
- [ESP MQTT](https://www.arduino.cc/reference/en/libraries/espmqttclient/)
- [PAHO MQTT](https://pypi.org/project/paho-mqtt/)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
