void loadConfig()
{
    File file = SPIFFS.open("/credentials.json", "r");
    if (!file)
    {
        Serial.println("Failed to open config file");
        return;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.println("Failed to read file, using default configuration");
    }

    file.close();

    WIFI_SSID = doc["wifiSSID"].as<String>();
    WIFI_PASSWORD = doc["wifiPassword"].as<String>();
    LINE_TOKEN = doc["lineToken"].as<String>();
    TS_USER_ID = doc["thingspeakUserID"].as<String>();
    TS_PASSOWRD = doc["thingspeakPassword"].as<String>();
    TS_CLIENT_ID = doc["thingspeakClientID"].as<String>();
    TS_CHANNEL_ID = doc["thingspeakChannelID"].as<String>();
    TS_WRITE_API = doc["thingspeakWriteAPI"].as<String>();
    TS_READ_API = doc["thingspeakReadAPI"].as<String>();
    AP_SSID = doc["apSSID"].as<String>();
    AP_PASSWORD = doc["apPassword"].as<String>();

    Serial.println("Configulation loaded");

    Serial.println("WiFi SSID : " + WIFI_SSID);
    Serial.println("User ID : " + TS_USER_ID);
    Serial.println("Channel ID : " + TS_CHANNEL_ID);
    Serial.println("AP SSID : " + AP_SSID);
}

void saveConfig(String _ssid, String _pass, String _user, String _tspass, 
                String _tsclient, String _channel, String _tswrite, String _tsread,
                String _line, String _apssid, String _appass)
{
    JsonDocument doc;

    doc["wifiSSID"] = _ssid;
    doc["wifiPassword"] = _pass;
    doc["thingspeakUserID"] = _user;
    doc["thingspeakPassword"] = _tspass;
    doc["thingspeakClientID"] = _tsclient;
    doc["thingspeakChannelID"] = _channel;
    doc["thingspeakWriteAPI"] = _tswrite;
    doc["thingspeakReadAPI"] = _tsread;
    doc["lineToken"] = _line;
    doc["apSSID"] = _apssid;
    doc["apPassword"] = _appass;

    File file = SPIFFS.open("/credentials.json", "w");
    if (!file)
    {
        Serial.println("Failed to open config file for writing");
        return;
    }

    serializeJson(doc, file);
    file.close();
    Serial.println("Config saved.");
}
