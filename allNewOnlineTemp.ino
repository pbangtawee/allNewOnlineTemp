/********************************* INCLUDE LIBRARY **********************************/
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

/******************************* DEVICE INFORMATION *********************************/
const String VERSION = "1.0.0";

/******************************** CONSTANT VARIABLE *********************************/
IPAddress AP_IP(192, 168, 4, 1);
IPAddress AP_GATEWAY(192, 168, 4, 1);
IPAddress SUBNET(255, 255, 255, 0);
const String HOST = "weather";
const int MQTT_PORT = 1883; 

/************************************* VARIABLE *************************************/
String WIFI_SSID = "";
String WIFI_PASSWORD = "";
String AP_SSID = "";
String AP_PASSWORD = "";
String LINE_TOKEN = "";
String TS_USER_ID = "";
String TS_PASSOWRD = "";
String TS_CLIENT_ID = "";
String TS_CHANNEL_ID = "";
String TS_WRITE_API = "";
String TS_READ_API = "";

/*********************************** INILIZATION ************************************/
WebServer SERVER(80);

/************************************** SETUP ***************************************/
void setup()
{
  Serial.begin(115200);
  Serial.println();

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting FS");
    return;
  }

  loadConfig();
  Serial.println("Config. loaded.");

  // set mDNS
  if (MDNS.begin(HOST))
  {
    Serial.println("mDNS responder started");
    MDNS.addService("http", "tcp", 80);
  }

  SERVER.on("/", HTTP_GET, handleHome);
  SERVER.on("/config", HTTP_GET, handleConfig);
  SERVER.on("/save", HTTP_POST, handleSave);
//   SERVER.on("/update", HTTP_GET, handleUpdateFirmware);
//   SERVER.on("/updatefirmware", HTTP_POST, handleFirmwareUpdateFinished, handleFirmwareUpload);

  SERVER.begin();
  Serial.println("HTTP server started");
}

/************************************** LOOP ****************************************/
void loop()
{
  SERVER.handleClient();
}