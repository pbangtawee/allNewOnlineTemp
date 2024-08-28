bool mqttConnect() 
{
  bool rc;

  rc = MQTT_SERVER.length() > 0;
  if (rc) {
    MQTT_CLIENT.setServer(MQTT_SERVER.c_str(), MQTT_PORT);
    Serial.println(String("Attempting ThingSpeak MQTT :") + MQTT_SERVER);

    rc = MQTT_CLIENT.connect(TS_CLIENT_ID.c_str(), TS_USER_ID.c_str(), TS_PASSOWRD.c_str());
    if (rc)
      Serial.println("Established :" + TS_CLIENT_ID);
    else
      Serial.println("Connection failed :" + String(MQTT_CLIENT.state()));
  }
  return rc;
}

bool mqttPublish(float _temp, float _humi) 
{
  bool reconnect;
  
  String topic = "channels/" + String(TS_CHANNEL_ID) + "/publish/" + String(TS_WRITE_API);
  String payload = String("field1=") + String(_temp) + "&field2=" + String(_humi);

  reconnect = !MQTT_CLIENT.connected();
  if (!reconnect)
    return MQTT_CLIENT.publish(topic.c_str(), payload.c_str());
  else
    return false;
}
