#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <uri/UriBraces.h>
#include "wifi.h"
#include "status_handlers.h"
#include "led_handlers.h"
#include "health_handlers.h"

#define BAUD 9600
#define LED D4
#define HTTP_REST_PORT 8080

const char *ssid = "NOWTVFGNGD";
const char *password = "3Yd4TIIbcXv9";

ESP8266WebServer server(HTTP_REST_PORT);

void setup () {
  Serial.begin(BAUD);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  connect_to_wifi(ssid, password);
  digitalWrite(LED, LOW);
  health_handlers(server);
  led_handlers(server);
  status_handlers(server);

  server.begin();
  digitalWrite(LED, HIGH);
}

void loop () {
  server.handleClient();
}
