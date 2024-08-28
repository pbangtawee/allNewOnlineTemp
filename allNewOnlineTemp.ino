/********************************* INCLUDE LIBRARY **********************************/
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>

/******************************* DEVICE INFORMATION *********************************/
const String VERSION = "1.0.0";

/*********************************** PIN DEFINE *************************************/
const int LED_STAT = 2;
const int HEARTBEAT_LED = 15;

/******************************** CONSTANT VARIABLE *********************************/
IPAddress AP_IP(192, 168, 4, 1);
IPAddress AP_GATEWAY(192, 168, 4, 1);
IPAddress SUBNET(255, 255, 255, 0);
const String HOST = "weather";
const String MQTT_SERVER = "mqtt3.thingspeak.com";
const int MQTT_PORT = 1883;
const int READ_SAMPLE = 5;
const int DATA_INTERVAL = 1;  // in minutes

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
float TEMPERATURE;
float HUMIDITY;

/************************************** TIMER ***************************************/
unsigned long LAST_GET_DATA;
unsigned long HEARTBEAT_TIME = 0;

/********************************* INITIALIZATION ***********************************/
WebServer SERVER(80);
WiFiClient CLIENT;
PubSubClient MQTT_CLIENT(CLIENT);
Adafruit_AHTX0 AHT_SENSOR;

/************************************** SETUP ***************************************/
void setup()
{
  Serial.begin(115200);
  Serial.println();

  /* Pin initialize */
  pinMode(LED_STAT, OUTPUT);
  pinMode(HEARTBEAT_LED, OUTPUT);

  digitalWrite(LED_STAT, HIGH);
  digitalWrite(HEARTBEAT_LED, LOW);

  /* Load all config */
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting FS");
    return;
  }
  loadConfig();

  /* Network connection */
  wifiConnect();
  checkConnection();

  /* Initialize */
  Wire.begin();
  AHT_SENSOR.begin();

  /* Set OTA update */
  otaSetup();

  /* set mDNS */
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

  mqttConnect();
  getWeatherData();
  mqttPublish(TEMPERATURE, HUMIDITY);
  LAST_GET_DATA = millis();
  digitalWrite(LED_STAT, LOW);
}

/************************************** LOOP ****************************************/
void loop()
{
  SERVER.handleClient();
  ArduinoOTA.handle();

    // Check wifi status and reconnect if request
    if (WiFi.status() != WL_CONNECTED)
    {
      wifiConnect();
    }

    // Get data interval
    if (millis() - LAST_GET_DATA >= DATA_INTERVAL * 60000)
    {
      digitalWrite(LED_STAT, HIGH);
      LAST_GET_DATA = millis();
      mqttConnect();
      getWeatherData();
      mqttPublish(TEMPERATURE, HUMIDITY);
      digitalWrite(LED_STAT, LOW);
    }

    // Heartbeat
    blink(HEARTBEAT_LED, HEARTBEAT_TIME, 250, 10000);
}
