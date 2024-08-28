String readPage(String path)
{
    File file = SPIFFS.open(path, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return "";
    }

    String content = "";
    while (file.available())
    {
        content += char(file.read());
    }
    file.close();
    return content;
}

void handleHome()
{
    String html = readPage("/index.html");

    html.replace("{ssid}", WIFI_SSID);
    html.replace("{password}", WIFI_PASSWORD);
    html.replace("{ts_user}", TS_USER_ID);
    html.replace("{ts_pass}", TS_PASSOWRD);
    html.replace("{ts_client}", TS_CLIENT_ID);
    html.replace("{ts_channel}", TS_CHANNEL_ID);
    html.replace("{ts_write}", TS_WRITE_API);
    html.replace("{ts_read}", TS_READ_API);
    html.replace("{line_token}", LINE_TOKEN);
    html.replace("{ap_ssid}", AP_SSID);
    html.replace("{ap_password}", AP_PASSWORD);

    SERVER.send(200, "text/html", html);
}

void handleConfig()
{
    String html = readPage("/setting.html");

    html.replace("{ssid}", WIFI_SSID);
    html.replace("{password}", WIFI_PASSWORD);
    html.replace("{ts_user}", TS_USER_ID);
    html.replace("{ts_pass}", TS_PASSOWRD);
    html.replace("{ts_client}", TS_CLIENT_ID);
    html.replace("{ts_channel}", TS_CHANNEL_ID);
    html.replace("{ts_write}", TS_WRITE_API);
    html.replace("{ts_read}", TS_READ_API);
    html.replace("{line_token}", LINE_TOKEN);
    html.replace("{ap_ssid}", AP_SSID);
    html.replace("{ap_password}", AP_PASSWORD);

    SERVER.send(200, "text/html", html);
}

void handleSave()
{
    // handle wifi settings
    String WIFISSID = SERVER.arg("wifi-ssid");
    String WIFIPASSWORD = SERVER.arg("wifi-password");
    String TSUSERID = SERVER.arg("ts-user");
    String TSPASSOWRD = SERVER.arg("ts-pass");
    String TSCLIENTID = SERVER.arg("ts-client");
    String TSCHANNELID = SERVER.arg("ts-channel");
    String TSWRITEAPI = SERVER.arg("ts-write");
    String TSREADAPI = SERVER.arg("ts-read");
    String LINETOKEN = SERVER.arg("line-token");
    String APSSID = SERVER.arg("ap-ssid");
    String APPASSWORD = SERVER.arg("ap-password");

    Serial.println("Saving new data.");
    Serial.println("Opening json file.");

    saveConfig(WIFISSID, WIFIPASSWORD, TSUSERID, TSPASSOWRD, TSCLIENTID,
               TSCHANNELID, TSWRITEAPI, TSREADAPI, LINETOKEN, APSSID, APPASSWORD);
    Serial.println("Saved data to json file.");

//    String html = readPage("/success.html");
//    SERVER.send(200, "text/html", html);

    // restart device
    delay(5000);
    ESP.restart();
}
