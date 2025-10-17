/*
*              Wortuhr
*               
*         Based on: https://github.com/prampec/IotWebConf
*                Own access point (AP) if no WIFI available
*                Configuration page in AP and while Client mode
*                Possibility to configure a lot of parameters (see IotWebConf Dokumentation)           
*
*         Added by Michael Graf, https://github.com/MichGraf
*                MQTT and OTA-Update as standard
*                NTP-Time support
*                Filesystem "LittleFS"
*                HTML-Page for File-Overview (Dir on filesystem)
*                Debugprint instead of Seriel.print to debug additional in HTML
*                HTML-Page for Debug-Output
*
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*
*          Without own changes the template works as MQTT-Logger (# subscribed)
*          with 5000 Char Debug buffer. Please check if this is necessary (normally to much)
*
*    ##############################################################################
*    This version is just the template or "operating system" for other projects.
*    Without changes it works as MQTT-Logger.
*    In Main.ccp you must just add your business logic to init, setup, loop, 
*       handle_root for the web-page, mqtt-message-received and mqqt-send. 
*    Thats all!!!! 
*    ##############################################################################
*/

#define Debugprint_size 1000   //Bytes Size of debug-buffer (recommended 1000..2000)
#define _serialprint         //adds output of debug-info to Serial additional to HTML-standard
#define _mqttsubscribe "/#"     //use mqtt or not, comment for no mqtt, just the wildcard, the prefix is in the configuration page

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char thingName[] = "WortuhrB";

// -- Initial password to connect to the Thing, when it creates an own Access Point.
const char wifiInitialApPassword[] = "25061960";

// -- Configuration specific key. The value should be modified if config structure was changed.
#define CONFIG_VERSION "conf_002"

/* just for Info D1 mini 8266 (!)
#define LED_BUILTIN 2
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;   
static const uint8_t D2   = 4;   
static const uint8_t D3   = 0;   //<be careful>
static const uint8_t D4   = 2;   //led builtin-LED !!
static const uint8_t D5   = 14;  
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t RX   = 3;
static const uint8_t TX   = 1;
*/

#define praesenz D1      //PINs der externen Peripherie
#define LDR A0
#define LED D2
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h> 



// -- When CONFIG_PIN is pulled to ground on startup, the Thing will use the initial
//      password to buld an AP. (E.g. in case of lost password)
#define CONFIG_PIN D4

// -- Status indicator pin.
//      First it will light up (kept LOW), on Wifi connection it will blink,
//      when connected to the Wifi it will turn off (kept HIGH).
#define STATUS_PIN LED_BUILTIN    //D4

/****************************( Definieren der Globale Variablen )**************************/
#include "template_init.h"




//###################################### iotWebConf - projektspezifischer Teil !!! #################################################################################################
bool mqtt_send_enable=false;
unsigned long last_millis, ticker, variantenticker;
int variante=0;

// projektspezifische Variablen
int enablenoise;
char enablenoise_val[10];

int min_helligkeit;
char min_helligkeit_val[NUMBER_LEN];
int max_helligkeit;
char max_helligkeit_val[NUMBER_LEN];
int nacht_helligkeit;
char nacht_helligkeit_val[NUMBER_LEN];


IotWebConfParameterGroup group1 = IotWebConfParameterGroup("group1", "Wortuhr-Parameter");
IotWebConfCheckboxParameter anablenoise_Param = IotWebConfCheckboxParameter("Enable Nois", "enablenoise", enablenoise_val, 10,  true);
IotWebConfNumberParameter min_helligkeit_param = IotWebConfNumberParameter("Lichtsensor Dunkelwert: LED min (0..)", "min_helligkeit_val", min_helligkeit_val, NUMBER_LEN, "0", "0..1024", "min='0' max='900' step='1'");
IotWebConfNumberParameter max_helligkeit_param = IotWebConfNumberParameter("Lichtsensor Hellwert: LED voll an (..1024)", "max_helligkeit_val", max_helligkeit_val, NUMBER_LEN, "1024", "0..9999", "min='100' max='9999' step='1'");
IotWebConfNumberParameter nacht_helligkeit_param = IotWebConfNumberParameter("Helligkeit nachts (0..10)", "nacht_helligkeit_val", nacht_helligkeit_val, NUMBER_LEN, "1", "0..10", "min='0' max='10' step='1'");

//###################################### Alle Parameter als string definieren.
///char val_wait[NUMBER_LEN];
//char val_helligkeit[NUMBER_LEN];
//char LaufschriftText[STRING_LEN] = "Willkommen in Michael's Bastelbude";  //Default Laufschrift
//###################################### Alle Parameter definieren.
//IotWebConfParameterGroup group1 = IotWebConfParameterGroup("group1", "Laufschrift");
//IotWebConfTextParameter par_LaufschriftText = IotWebConfTextParameter("Laufschrift-Text", "laufschrifttext", LaufschriftText, STRING_LEN);
//IotWebConfNumberParameter par_wait = IotWebConfNumberParameter("Geschwindigkeit (1..255)", "val_wait", val_wait, NUMBER_LEN, "50", "1..255", "min='1' max='255' step='1'");
//IotWebConfNumberParameter par_helligkeit = IotWebConfNumberParameter("Helligkeit (0..15)", "val_helligkeit", val_helligkeit, NUMBER_LEN, "3", "0..15", "min='0' max='15' step='1'");
//###################################### Number und andere Parameter als eigentliche Variable definieren
//unsigned long wait = 50;                  //Zeit in ms für Scroll Geschwindigkeit wo gewartet wird, unsigned long to avoid warning while miilis() calculation
//int helligkeit = 3;                        //Default Helligkeit 0 bis 15
//###################################### Number und andere Parameter umwandeln
void val_init()
{
//helligkeit = atoi(val_helligkeit);
//wait = atoi(val_wait);
// Laufschrifttext ist ohnehin string, keine Wandlung nötig
//matrix.setIntensity(helligkeit);   //und gleich einstellen...

if (strcmp(enablenoise_val, "selected")==0) enablenoise=1;else enablenoise=0;
Debugprint("Enable Noise Val ");
Debugprintln(enablenoise_val);
Debugprint("Enable Noise ");
Debugprintln(enablenoise);

min_helligkeit=atoi(min_helligkeit_val);
max_helligkeit=atoi(max_helligkeit_val);
nacht_helligkeit=atoi(nacht_helligkeit_val);
}
//###################################### Einrichtungsroutine, wird im Template_Setup aufgerufen
void conf_init()
{
iotWebConf.addParameterGroup(&group1);
group1.addItem(&anablenoise_Param);
group1.addItem(&min_helligkeit_param);
group1.addItem(&max_helligkeit_param);
group1.addItem(&nacht_helligkeit_param);
}
//###########################################################################################################################################################################################



/* weitere Beispiele !!!!!!!!!
//###################################### Alle Parameter als string definieren.
char stringParamValue[STRING_LEN];
char par_brightnesValue[NUMBER_LEN];

char checkboxParamValue[STRING_LEN];
char farbeParamValue[STRING_LEN];

static char farbeValues[][STRING_LEN] = { "konstant", "rainbow", "zufall" };
static char farbeNames[][STRING_LEN] = { "Konstant", "Rainbow", "Zufall" };

//###################################### Alle Parameter zusätzlich als Werte definieren.
uint8_t val_brightnes;


IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);
// -- You can also use namespace formats e.g.: iotwebconf::TextParameter
IotWebConfTextParameter stringParam = IotWebConfTextParameter("Bezeichnung", "stringParam", stringParamValue, STRING_LEN);

IotWebConfParameterGroup group1 = IotWebConfParameterGroup("group1", "Farbe");

IotWebConfSelectParameter farbeParam = IotWebConfSelectParameter("Farbmodus", "farbeParam", farbeParamValue, STRING_LEN, (char*)farbeValues, (char*)farbeNames, sizeof(farbeValues) / STRING_LEN, STRING_LEN);

IotWebConfNumberParameter par_b = IotWebConfNumberParameter("Blau (120)", "par_b", par_bValue, NUMBER_LEN, "50", "0..255", "min='0' max='255' step='1'");

IotWebConfCheckboxParameter checkboxParam = IotWebConfCheckboxParameter("Check param", "checkParam", checkboxParamValue, STRING_LEN,  true);

IotWebConfParameterGroup mqttGroup = IotWebConfParameterGroup("MQTT configuration","MQTT configuration");
IotWebConfTextParameter mqttServerParam = IotWebConfTextParameter("MQTT server", "mqttServer", mqttServerValue, STRING_LEN);
IotWebConfTextParameter mqttUserNameParam = IotWebConfTextParameter("MQTT user", "mqttUser", mqttUserNameValue, STRING_LEN);
IotWebConfPasswordParameter mqttUserPasswordParam = IotWebConfPasswordParameter("MQTT password", "mqttPass", mqttUserPasswordValue, STRING_LEN);
*/

unsigned long lwait;
int helli=20;
int enable_es_ist;
int savepraesenz=0;
int lauflicht;

/*
int stat_warnung_a=0;
int stat_warnung_b=0;
int stat_warnung_c=0;
int stat_warnung_e=0;
int stat_warnung_f=0;
int stat_warnung_g=0;

int stat_michael=0;
int stat_renate=0;
int stat_sommer=0;
int stat_winter=0;
int stat_weihnachten=0;

int stat_Solar_links=0;
int stat_Solar_rechts=0;
int stat_Laden_links=0;
int stat_Laden_rechts=0;
*/

int temp=0;

//unsigned long lastsolar, lastladen,lastpraesenz;
unsigned long lastpraesenz;


//###################################################################################################################
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;

#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;


uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;

  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }

  return i;
}

// The leds
CRGB leds[kMatrixWidth * kMatrixHeight];

// The 32bit version of our coordinates
static uint16_t xx;
static uint16_t yy;
static uint16_t zz;

// We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// use the z-axis for "time".  speed determines how fast time moves forward.  Try
// 1 for a very slow moving effect, or 60 for something that ends up looking like
// water.
// uint16_t speed = 1; // almost looks like a painting, moves very slowly
uint16_t speed = 20; // a nice starting speed, mixes well with a scale of 100
// uint16_t speed = 33;
// uint16_t speed = 100; // wicked fast!

// Scale determines how far apart the pixels in our noise matrix are.  Try
// changing these values around to see how it affects the motion of the display.  The
// higher the value of scale, the more "zoomed out" the noise iwll be.  A value
// of 1 will be so zoomed in, you'll mostly see solid colors.

// uint16_t scale = 1; // mostly just solid colors
// uint16_t scale = 4011; // very zoomed out and shimmery
uint16_t scale = 711;

// This is the array that we keep our computed noise values in
uint16_t noise[MAX_DIMENSION][MAX_DIMENSION];

//####################################################################################################################
#include "layout13x13_V1.h"
//#include "layout.h"
#include "logik.h"








//#################################################################################################################  Setup
void setup() 
{

//iotWebConf.skipApStartup();   //comment if AP should be run at startup per default

#include "Template_setup.h"

min_helligkeit=0;
max_helligkeit=1024;

val_init();     // Variablen aus der gespeicherten config vorbelegen
last_millis=ticker=variantenticker=millis();
//lastsolar=lastladen=millis()+700000;    // erst mal aus
lastpraesenz=0;
lwait=200;
lauflicht=0;

//#########################
  delay(3000);
  FastLED.addLeds<WS2812,LED,GRB>(leds,NUM_LEDS);
  FastLED.setBrightness(255);

  // Initialize our coordinates to some random values
  xx = random16();
  yy = random16();
  zz = random16();
  //########################


}
  //########################
// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8() {
  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
      noise[i][j] = inoise8(xx + ioffset,yy + joffset,zz);
    }
  }
  zz += speed;


}
  //########################

//#################################################################################################################  Loop
void loop() 
{

int noiseval=0;
//int tmp=0;
int hue=0;
int sat=0;
//int showsolar=0;
//int showladen=0;

#include "Template_loop.h"


if (mqtt_send_enable) {
      mqttSend();
      mqtt_send_enable=false;
}

if ((digitalRead(praesenz)!=0) && (enablenoise>0) && (tm.tm_sec==0)) noiseval=helli/3; // drittel Helligkeit bei Noise. Bei Helligkeit=1 -> 0. Nachts also nicht

  //########################   läuft eigentlich unnötigerweise immer - Beispiel aus den FastLed-Examples
 static uint8_t ihue=0;
  fillnoise8();
  for(int i = 0; i < kMatrixWidth; i++) {
    for(int j = 0; j < kMatrixHeight; j++) {

      //leds[XY(i,j)] = CHSV(noise[j][i],255,noiseval);

      // You can also explore other ways to constrain the hue used, like below
      leds[XY(i,j)] = CHSV(ihue + (noise[j][i]>>2),255,noiseval);
    }
  }
  ihue+=1;

if (temp>=0) {hue=30; sat=map(temp,0,30,0,255);}          //zwischen 0 und 30 Grad eher gelb/orange, vermeidet schweinchenrosa, ab 30 Grad wirds rot
else {hue=150; sat=map(temp,-25,0,255,0);}                //bei Minustemperauren eher blau
if (temp>=30) {sat=255; hue=map(temp,30,40,30,0);}         //durch die Steuerung der Saturation um die 0 Grad weiss -Y wie Schnee


 if ((millis()-last_millis) > lwait) {    //bestimmt auch die Lauflichtgeschwindigkeit

   helli=analogRead(LDR);
   if (helli<min_helligkeit) helli=min_helligkeit;
   if (helli>max_helligkeit) helli=max_helligkeit;

   helli=map(helli, min_helligkeit, max_helligkeit, nacht_helligkeit, 255);

   if (digitalRead(praesenz)==1) lastpraesenz=millis();
   if (millis()-lastpraesenz>7200000) helli=nacht_helligkeit;   //2h fix - to do:Variabel

   if (noiseval==0) Uhrlogik(hue,sat,helli);

   // Anzeige von Solar bzw. Laden: Wenn 10 Minuten kein Signal erhalten, erlischt die Anzeige (lastsolar...)
   // Wenn die Werte zu geringfügig erlischt die Anzeige (z.B. nachts keine Azeige von Solar)
   // Wenn beides angezeigt werden soll wechselt die Anzeige jede Minute

  //if ((millis()-lastsolar<650000) && ((stat_Solar_links+stat_Solar_rechts) > 50)) {showsolar=1; tmp++;}   // keine, eine oder zwei Wertanzeige
  //if ((millis()-lastladen<650000) && ((stat_Laden_links+stat_Laden_rechts) > 200)) {showladen=1;tmp++;}


  /*    if (showsolar && ((tmp==1) || (tm.tm_min % 2)) ) {  //ungrade Minuten wenn beides angezeigt, sonst immer
       Set_Text(w_solar,0,180,helli/2);
       for (int x=0; x<map(stat_Solar_links, 0, 600, 0, 6); x++)  leds[XY(x,12)] = CHSV(0,180,helli/2);
       for (int x=12; 12-x<map(stat_Solar_rechts, 0, 600, 0, 6); x--)  leds[XY(x,12)] = CHSV(0,180,helli/2);
      }


     if (showladen && ((tmp==1) || ((tm.tm_min % 2) == 0))) {  // gerade Minuten
       //Set_Text(w_laden,150,180,helli);
       Set_Laden(150,180,helli/2);
       if (stat_Laden_links>5000) stat_Laden_links=6000;    // bei 2000 3 Pfeile, bei 11000 6 Pfeile plus X
       if (stat_Laden_rechts>5000) stat_Laden_rechts=6000;
       for (int x=0; x<map(stat_Laden_links, 0, 5000, 0, 6); x++)  leds[XY(x,12)] = CHSV(150,180,helli/2);
       for (int x=12; 12-x<map(stat_Laden_rechts, 0, 5000, 0, 6); x--)  leds[XY(x,12)] = CHSV(150,180,helli/2);
     }


// erzeuge Lauflichteffekt bei der Werteanzeige
for (int x=0+lauflicht; x<13-lauflicht; x++)  leds[XY(x,12)] = CHSV(150,180,0);
lauflicht++;
if (lauflicht==6) lauflicht=0;



   if (stat_warnung_a>0) Set_Text(w_warnung_a, stat_warnung_a, 255, helli/2);
   if (stat_warnung_b>0) Set_Text(w_warnung_b, stat_warnung_b, 255, helli/2);
   if (stat_warnung_c>0) Set_Text(w_warnung_c, stat_warnung_c, 255, helli/2);
   if (stat_warnung_e>0) Set_Text(w_warnung_e, stat_warnung_e, 255, helli/2);
   if (stat_warnung_f>0) Set_Text(w_warnung_f, stat_warnung_f, 255, helli/2);
   if (stat_warnung_g>0) Set_Text(w_warnung_g, stat_warnung_g, 255, helli/2);

   if (stat_michael>0) Set_Text(w_michael, stat_michael, 255, helli/2);
   if (stat_renate>0) Set_Text(w_renate, stat_renate, 255, helli/2);
   if (stat_sommer>0) Set_Text(w_sommer, stat_sommer, 255, helli/2);
   if (stat_winter>0) Set_Text(w_winter, stat_winter, 255, helli/2);
   if (stat_weihnachten>0) Set_Text(w_weihnachten, stat_weihnachten, 255, helli/2);

*/

    FastLED.show();
    last_millis=millis();

    }
  //########################

   if ((millis()-ticker) > 1000) {
    if (digitalRead(praesenz) != savepraesenz) {mqttSend(); savepraesenz=digitalRead(praesenz);}
    ticker=millis();
   }
}



//#################################################################################################################
//######################## Web-Request Handler and Callback-Functions #############################################
/**
 * Handle web requests to "/" path.
 */
void handleRoot()                 // definiert die Webseite, nicht die config-Seite!
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<meta http-equiv=\"refresh\" content=\"5\">";
  s += "<title>";
  s += stringParamValue;
  s += "</title></head><body>";
  s += "Ueberschrift";
  s += "<br>";
  s += "<ul>";
   s += "<li>Datum: ";
  s += tm.tm_mday;
  s += " : ";
  s += tm.tm_mon+1;
  s += " : ";
  s += tm.tm_year+1900;
  s += "<li>Time: ";
  s += tm.tm_hour;
  s += " : ";
  s += tm.tm_min;
  s += " : ";
  s += tm.tm_sec;
  
  s += "<br><li>Free Heap: ";
  s += ESP.getFreeHeap();

  s += "</ul>";

  s += "<br> Gemessene Helligkeit: ";
  s += analogRead(LDR);
  s += "<br> Anzeigevariante: ";
  s += variante;
 /* 
   s += "<br> Helligkeit: ";
  s += helligkeit;
  s += "<br> Geschwindigkeit: ";
  s += wait;
*/
 
  s += "<br><br> MQTT-Server: ";
  s += mqttServerValue;
  s += "<br> Publish/Subscribe to: ";
  s += mqttsubscribe;

  s += "<br><br><br> Go to <a href='config'>configure page</a> to change values.";
  s += "<br>Go to <a href='file'>File-page</a> to look at the file system.";
  s += "<br>Go to <a href='log'>Log-page</a> to look at the logfile."; 
  s += "</body></html>\n";
  server.send(200, "text/html", s);
}


bool formValidator(iotwebconf::WebRequestWrapper* webRequestWrapper)    //Plausibilisieret die Eingaben auf der config-Seite, false->Ablehnung der Einstellungen
{
  //Serial.println("Validating form.");
  Htmlprintln("Validating form.");
  bool valid = true;

  int l = webRequestWrapper->arg(mqttServerParam.getId()).length();
  if (l < 3)
  {
    mqttServerParam.errorMessage = "Please provide at least 3 characters!";
    valid = false;
  }

  return valid;
}


void mqttMessageReceived(String &topic, String &payload)
{
  
  //Serial.println("Incoming: " + topic + " - " + payload);
  Debugtime();
  Htmlprintln("Rec: " + topic + " - " + payload);
  if (payload.length()>0) {            //leere Messages (z.B. zum Beenden von einem retained-Status werden ignoriert
    int x;
    String s;
    boolean wert, change = false;
    x=payload.length()+1;
    if (x>127) x=127;              // vermeidet Überlauf
    s=mqttsubscribe;
    // if (payload=="on" || payload=="ON" || payload=="an" || payload=="ein" || payload=="true" || payload=="1") wert=false; else wert=true; // !! negative Logik der Relais
    // if (topic==s+"/SetRel1") {RelState[1]=wert;  change=true;}
 
    /*   
    if (topic==s+"/SetSolar_links") {stat_Solar_links=payload.toInt();  lastsolar=millis(); change=true;}
    if (topic==s+"/SetSolar_rechts") {stat_Solar_rechts=payload.toInt();  lastsolar=millis();  change=true;}
    if (topic==s+"/SetLaden_links") {stat_Laden_links=payload.toInt();  lastladen=millis();  change=true;}
    if (topic==s+"/SetLaden_rechts") {stat_Laden_rechts=payload.toInt();  lastladen=millis();  change=true;}

// payload = hue, sat =255
    if (topic==s+"/SetWarnung_A") {stat_warnung_a=payload.toInt(); change=true;}
    if (topic==s+"/SetWarnung_B") {stat_warnung_b=payload.toInt(); change=true;}
    if (topic==s+"/SetWarnung_C") {stat_warnung_c=payload.toInt(); change=true;}
    if (topic==s+"/SetWarnung_E") {stat_warnung_e=payload.toInt(); change=true;}
    if (topic==s+"/SetWarnung_F") {stat_warnung_f=payload.toInt(); change=true;}
    if (topic==s+"/SetWarnung_G") {stat_warnung_g=payload.toInt(); change=true;}
      
    if (topic==s+"/SetMichael") {stat_michael=payload.toInt(); change=true;}
    if (topic==s+"/SetRenate") {stat_renate=payload.toInt(); change=true;}
    if (topic==s+"/SetSommer") {stat_sommer=payload.toInt(); change=true;}
    if (topic==s+"/SetWinter") {stat_winter=payload.toInt(); change=true;}
    if (topic==s+"/SetWeihnachten") {stat_weihnachten=payload.toInt(); change=true;}
*/
    if (topic==s+"/SetTemp") {temp=payload.toInt(); change=true;}

 //   if (topic==s+"/Reset") {stat_warnung_a=stat_warnung_b=stat_warnung_c=stat_warnung_e=stat_warnung_f=stat_warnung_g=0;
 //                           lastsolar=lastladen=millis()+700000;
 //                           change=true;}

  }
}

void mqttSend() {
  String s;

  if ((iotWebConf.getState() == iotwebconf::OnLine) && (mqttClient.connected())) {

   s=mqttsubscribe;
   Htmlprintln("Publish Status");

   if (digitalRead(praesenz)) mqttClient.publish(s+"/Praesenz","anwesend"); else mqttClient.publish(s+"/Praesenz","abwesend");
   
  }
}

#include "Template_post.h"
// hier ist Schluss

