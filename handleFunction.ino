String readPage(String path)
{
    File file = LittleFS.open(path, "r");
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

    String rep_speed = String(MOTOR_SPEED);
    String rep_angle = String(ROTATION_DEGREE);
    
    html.replace("{speed}", rep_speed);
    html.replace("{angle}", rep_angle);
    html.replace("{apname}", AP_SSID);
    html.replace("{appassword}", AP_PASSWORD);
    html.replace("{version}", VERSION);

    SERVER.send(200, "text/html", html);
}

void handleConfig()
{
    String html = readPage("/setting.html");

    String rep_speed = String(MOTOR_SPEED);
    String rep_angle = String(ROTATION_DEGREE);
    
    html.replace("{speed}", rep_speed);
    html.replace("{angle}", rep_angle);
    html.replace("{apname}", AP_SSID);
    html.replace("{appassword}", AP_PASSWORD);
    html.replace("{version}", VERSION);

    SERVER.send(200, "text/html", html);
}

void handleSave()
{
    // handle wifi settings
    String Speed = SERVER.arg("speed");
    String Angle = SERVER.arg("angle");
    String ApSsid = SERVER.arg("ap-name");
    String ApPassword = SERVER.arg("ap-password");

    Serial.println("Saving new data.");
    Serial.println("Opening json file.");

    saveConfig(Speed.toInt(), Angle.toInt(), String(ApSsid), String(ApPassword));
    Serial.println("Saved data to json file.");

//    String html = readPage("/success.html");
//    SERVER.send(200, "text/html", html);

    // restart device
    delay(5000);
    ESP.restart();
}
