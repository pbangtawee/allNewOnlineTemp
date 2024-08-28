void wifiConnect()
{
    int tryConn = 0;

    // connect to wifi
    WiFi.mode(WIFI_STA);
    Serial.print("Connect to WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED && tryConn < 100)
    {
        delay(150);
        Serial.print(".");
        tryConn++;
    }
}

void checkConnection()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    apSetup();
  }
  else
  {
    staSetup();
  }
}

void apSetup()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    Serial.println("\nStarted Access Point.");
}

void staSetup()
{
    // Get first time data
    mqttConnect();
    getWeatherData();
    mqttPublish(TEMPERATURE, HUMIDITY);
    LAST_GET_DATA = millis();
}
