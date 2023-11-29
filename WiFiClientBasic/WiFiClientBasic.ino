#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "Ganna"
#define STAPSK  "ganna2003"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.2";
const uint16_t port = 12344;

int outputpin = A0;
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("Connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("Connection failed");
    Serial.println("Waiting 5 sec...");
    delay(5000);
    return;
  }

  Serial.println("Connected to server");

  client.println("hello from ESP8266");

  Serial.println("Sending data to server");

  // Read back one line from the server
  Serial.println("Receiving from remote server");
  String line = client.readStringUntil('\r');
  Serial.println(line);

  Serial.println("Closing connection");
  client.stop();

  Serial.println("Waiting 5 sec...");
  delay(5000);

  int analogValue = analogRead(outputpin);
  float millivolts = (analogValue / 1024.0) * 3300;
  float celsius = millivolts / 10;

  Serial.print("Temperature in Celsius: ");
  Serial.println(celsius);

  // Send temperature data to the server
  client.connect(host, port);
  client.print(celsius);
  client.stop();

  // Calculate Fahrenheit
  float fahrenheit = (celsius * 9) / 5 + 32;
  Serial.print("Temperature in Fahrenheit: ");
  Serial.println(fahrenheit);

  Serial.println("Waiting 5 sec...");
  delay(5000);
}
