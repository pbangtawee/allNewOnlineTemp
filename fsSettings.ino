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
    TS_USER_ID= doc["thingspeakUserID"].as<String>();
    TS_PASSOWRD = doc["thingspeakPassword"].as<String>();
    TS_CLIENT_ID = doc["thingspeakClientID"].as<String>();
    TS_CHANNEL_ID = doc["thingspeakChannelID"].as<String>();
    TS_WRITE_API = doc["thingspeakWriteAPI"].as<String>();
    TS_READ_API = doc["thingspeakReadAPI"].as<String>();
    AP_SSID = doc["apSSID"].as<String>();
    AP_PASSWORD = doc["apPassword"].as<String>();

    Serial.println("Configulation loaded");
}

void saveConfig()
{
    JsonDocument doc;

    doc["wifiSSID"] = WIFI_SSID;
    doc["wifiPassword"] = WIFI_PASSWORD;
    doc["lineToken"] = LINE_TOKEN;
    doc["thingspeakUserID"] = TS_USER_ID;
    doc["thingspeakPassword"] = TS_PASSOWRD;
    doc["thingspeakClientID"] = TS_CLIENT_ID;
    doc["thingspeakChannelID"] = TS_CHANNEL_ID;
    doc["thingspeakWriteAPI"] = TS_WRITE_API;
    doc["thingspeakReadAPI"] = TS_READ_API;
    doc["apSSID"] = AP_SSID;
    doc["apPassword"] = AP_PASSWORD;

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
