  Serial.begin(115200);
  Serial.println();
  Htmlprint_init();

  //Serial.println("Starting up...");
  Htmlprintln("Starting up...");

  mqttGroup.addItem(&mqttServerParam);
  mqttGroup.addItem(&mqttUserNameParam);
  mqttGroup.addItem(&mqttUserPasswordParam);
  mqttGroup.addItem(&mqttSubscribe);
  
   
  iotWebConf.setStatusPin(STATUS_PIN);
  iotWebConf.setConfigPin(CONFIG_PIN);
  iotWebConf.addSystemParameter(&stringParam);
  iotWebConf.addParameterGroup(&mqttGroup);
  iotWebConf.setConfigSavedCallback(&configSaved);
  iotWebConf.setFormValidator(&formValidator);
  iotWebConf.getApTimeoutParameter()->visible = true;
  iotWebConf.setWifiConnectionCallback(&wifiConnected);

  // -- Define how to handle updateServer calls.
  iotWebConf.setupUpdateServer(
    [](const char* updatePath) { httpUpdater.setup(&server, updatePath); },
    [](const char* userName, char* password) { httpUpdater.updateCredentials(userName, password); });

  conf_init(); // projektspezifische Konfig-Page

  // -- Initializing the configuration.
  bool validConfig = iotWebConf.init();
  if (!validConfig)
  {
    mqttServerValue[0] = '\0';
    mqttUserNameValue[0] = '\0';
    mqttUserPasswordValue[0] = '\0';
  }
  

  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", []{ iotWebConf.handleConfig(); });
  server.on("/file", []{handleFile(); });
  server.on("/log", []{handleLog(); });
  server.onNotFound([](){ iotWebConf.handleNotFound(); });

  mqttClient.begin(mqttServerValue, net);
  mqttClient.onMessage(mqttMessageReceived);
  
  if (LittleFS.begin()) Htmlprintln("Filesystem ok"); else Htmlprintln("Filesystem failed");

  //##################################################################################  NTP-Server
 #ifdef ESP8266
     configTime(My_TZ, My_NTP_Server);
#elif defined(ESP32)
     configTzTime(My_TZ, My_NTP_Server);
#endif

