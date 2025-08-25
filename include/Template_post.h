void handleFile()
{
  
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>";
  s += stringParamValue;
  s += "</title></head><body>";
  s += "<ul>";
  s += "<li>File System Info: ";
  s += "<br> <br>";
  
  /*
  FSInfo fs_info;
  LittleFS.info(fs_info);
 
  s += "Total space:      ";
  s += fs_info.totalBytes;
  s += " byte <br>";
  s += "Total space used: ";
  s += fs_info.usedBytes;
  s += " byte <br>";
  s += "Block size:       ";
  s += fs_info.blockSize;
  s += " byte <br>";
  s += "Page size:        ";
  s += fs_info.totalBytes;
  s += " byte <br>";
 
  //  Serial.print("Max open files:   ");
  //  Serial.println(fs_info.maxOpenFiles);
 
  //  Serial.print("Max path lenght:  ");
  //  Serial.println(fs_info.maxPathLength);
  s += "<br>";
  s += "<li>Files: <br><br>";
Dir dir=LittleFS.openDir("/");
while (dir.next()) {
  s += dir.fileName();
  s += " : ";
  s += dir.fileSize();
  s += "<br>";
}
*/  s+="LittleFS does not work in the  moment";

  s += "</ul>";
  s += "</body></html>\n";

  server.send(200, "text/html", s);
}

void handleLog()
{
  String s1 = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s1 += "<meta http-equiv=\"refresh\" content=\"2\">";  //alle 10 Sek refresh
  s1 += "<title>";
  s1 += stringParamValue;
  s1 += "</title></head><body>";
  s1 += "<ul>";
  s1 += "<li>Log/Debug Info: ";
  s1 += "<br><li>Free Heap: ";
  s1 += ESP.getFreeHeap();
  s1 += "<br> <br>";
  //s += printstr;
  String s2 = "<br>";
  s2 += "</ul>";
  s2 += "</body></html>\n";

  server.send(200, "text/html", s1+printstr+s2);
}

void wifiConnected()
{
  needMqttConnect = true;
  iotWebConf.blink(100,0); //always off
  iotWebConf.disableBlink();
  digitalWrite(LED_BUILTIN, HIGH); // Ausschalten
  Htmlprintln("WiFi connected");
}

void configSaved()
{
  //Serial.println("Configuration was updated.");
  Htmlprintln("Configuration was updated.");
  //mqttSend();
  val_init();

}

bool connectMqtt() {
  String xxx;
  #ifdef _mqttsubscribe
    xxx=mqttsubscribe;
    xxx=xxx+_mqttsubscribe;
    unsigned long now = millis();
    if (1000 > now - lastMqttConnectionAttempt)
    {
      // Do not repeat within 1 sec.
      return false;
    }
    Htmlprint("Connecting to MQTT server...");
    Htmlprintln(mqttServerValue);
    if (!connectMqttOptions()) {
      lastMqttConnectionAttempt = now;
      return false;
    }
    Htmlprint("MQTT connected! as ");
    Htmlprintln(iotWebConf.getThingName());
    Debugprint(xxx);
    Debugprintln(" subscribed");
    if (strlen(mqttsubscribe)>0) mqttClient.subscribe(xxx); else mqttClient.subscribe("#");
  #endif

  return true;
}

bool connectMqttOptions()
{
  bool result;
  if ((mqttUserPasswordValue[0] != '\0') or (mqttUserNameValue[0] != '\0') )
  {
    result = mqttClient.connect(iotWebConf.getThingName(), mqttUserNameValue, mqttUserPasswordValue);
  }
  else if (mqttUserNameValue[0] != '\0')
  {
    result = mqttClient.connect(iotWebConf.getThingName(), mqttUserNameValue);
  }
  else
  {
    result = mqttClient.connect(iotWebConf.getThingName());
  }
  return result;
}

