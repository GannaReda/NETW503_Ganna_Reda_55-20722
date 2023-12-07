#include "ThingsBoard.h"
#include <ESP8266WiFi.h>
#include <DHT11.h>

DHT11 dht11(2);
#define WIFI_AP             "LA_Home"   
#define WIFI_PASSWORD       "miniesy2" 


#define TOKEN               "ckp27KrZpJpJXxkGxQIh" 
#define THINGSBOARD_SERVER  "demo.thingsboard.io"


WiFiClient espClient;

ThingsBoard tb(espClient);

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  InitWiFi();
}

void loop() {
  delay(1000);

  int temperature = dht11.readTemperature();
  
  Serial.println("temperature");
  Serial.println(temperature);
  if (WiFi.status() != WL_CONNECTED) {
    reconnect();
  }
  tb.connect(THINGSBOARD_SERVER, TOKEN);

  tb.sendTelemetryInt("temperature", temperature);

  tb.loop();
}

void InitWiFi()
{

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected WIFI");
}

void reconnect() {

  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to WIFI");
    
  }
}
