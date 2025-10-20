//##################################################################################  IOT

  // -- doLoop should be called as frequently as possible.
  iotWebConf.doLoop();
  mqttClient.loop();

  time(&now);
  localtime_r(&now,&tm);
  if (tm.tm_sec == 0) new_min=true; else new_min=false;

  if (needMqttConnect)
  {
    if (connectMqtt())
    {
      needMqttConnect = false;
    }
  }
  else if ((iotWebConf.getState() == iotwebconf::OnLine) && (!mqttClient.connected()))
  {
    //Serial.println("MQTT reconnect");
    if (!mqttClient.connected()) Htmlprintln("MQTT not connected");
    Htmlprintln("MQTT reconnect");
    connectMqtt();
  }

  if (needReset)
  {
    //Serial.println("Rebooting after 1 second.");
    Htmlprintln("Rebooting after 1 second.");
    iotWebConf.delay(1000);
    ESP.restart();
  }