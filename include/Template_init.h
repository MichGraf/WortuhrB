#include <MQTT.h>
#include <IotWebConf.h>
#include <IotWebConfUsing.h> // This loads aliases for easier class names.

#include <LittleFS.h>

int mqttdebug = 0;
String mqttprint="";


// UpdateServer includes
#ifdef ESP8266
# include <ESP8266HTTPUpdateServer.h>
#elif defined(ESP32)
// For ESP32 IotWebConf provides a drop-in replacement for UpdateServer.
# include <IotWebConfESP32HTTPUpdateServer.h>
#endif

//################################### ?? muss das so lang sein
#define STRING_LEN 128
#define NUMBER_LEN 32

// -- Method declarations.
void handleRoot();
void handleFile();
void handleLog();
void mqttMessageReceived(String &topic, String &payload);
bool connectMqtt();
bool connectMqttOptions();
// -- Callback methods.
void wifiConnected();
void configSaved();
bool formValidator(iotwebconf::WebRequestWrapper* webRequestWrapper);

DNSServer dnsServer;
WebServer server(80);

#ifdef ESP8266
ESP8266HTTPUpdateServer httpUpdater;
#elif defined(ESP32)
HTTPUpdateServer httpUpdater;
#endif

WiFiClient net;
MQTTClient mqttClient;

char stringParamValue[STRING_LEN];
char mqttServerValue[STRING_LEN];
char mqttUserNameValue[STRING_LEN];
char mqttUserPasswordValue[STRING_LEN];
char mqttsubscribe[STRING_LEN];

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);
// -- You can also use namespace formats e.g.: iotwebconf::TextParameter
IotWebConfTextParameter stringParam = IotWebConfTextParameter("Web-Titel", "stringParam", stringParamValue, STRING_LEN);

IotWebConfParameterGroup mqttGroup = IotWebConfParameterGroup("MQTT configuration","MQTT configuration");
IotWebConfTextParameter mqttServerParam = IotWebConfTextParameter("MQTT server", "mqttServer", mqttServerValue, STRING_LEN);
IotWebConfTextParameter mqttUserNameParam = IotWebConfTextParameter("MQTT user", "mqttUser", mqttUserNameValue, STRING_LEN);
IotWebConfPasswordParameter mqttUserPasswordParam = IotWebConfPasswordParameter("MQTT password", "mqttPass", mqttUserPasswordValue, STRING_LEN);
IotWebConfTextParameter mqttSubscribe = IotWebConfTextParameter("Subscribe (ohne #)", "mqttSubscribe", mqttsubscribe, STRING_LEN);

bool needMqttConnect = false;
bool needReset = false;
int pinState = HIGH;
unsigned long lastReport = 0;
unsigned long lastMqttConnectionAttempt = 0;



//##################################################################################  NTP-Server
#define My_NTP_Server "de.pool.ntp.org"
#define My_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"

#include "time.h"

void mqttSend();

time_t now;
tm tm;
/*   Info über verfügbare Zeitinfos
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
#ifdef __TM_GMTOFF
  long	__TM_GMTOFF;
#endif
#ifdef __TM_ZONE
  const char *__TM_ZONE;
*/

//######################################################################printstr
String printstr;

void Htmlprint_init() {
  printstr.reserve(Debugprint_size+10);  //+10 sicherheitshalber
  for (int i=0; i<Debugprint_size; i++) printstr += " ";
}

void Htmlprint(String s) {
  String ss=mqttsubscribe;
  if (s.length()>Debugprint_size) s="Debug to long";
  printstr.remove(0,s.length());
  printstr+=s;
  if (mqttdebug) mqttprint+=s;
  #ifdef _serialprint
      Serial.print(s);
  #endif
}
void Htmlprintln(String s) {
  String ss=mqttsubscribe;
  if (s.length()>Debugprint_size-4) s="Debug to long";
  printstr.remove(0,s.length()+4);
  printstr+=s;
  printstr+="<br>";
  if (mqttdebug) {
    if ((iotWebConf.getState() == iotwebconf::OnLine) && (mqttClient.connected())) {mqttClient.publish(ss+"/Debug",mqttprint+s); mqttprint="";}
    }
  
  
  #ifdef _serialprint
    Serial.println(s);
  #endif
}

#define Debugtime() Htmlprint(String(tm.tm_hour)+":"+String(tm.tm_min)+":"+String(tm.tm_sec)+" : ")
#define Debugprint(x) Htmlprint(String(x))
#define Debugprintln(x) Htmlprintln(String(x))
//######################################################################printstr
