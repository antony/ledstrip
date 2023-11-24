#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <uri/UriBraces.h>

#define BAUD 9600
#define LED D4
#define HTTP_REST_PORT 8080

const char *ssid = "NOWTVFGNGD";
const char *password = "3Yd4TIIbcXv9";

WiFiClient client;
ESP8266WebServer server(HTTP_REST_PORT);

void connect_to_wifi () {
   Serial.println();
   Serial.println();
   Serial.print("Connecting to WiFi");
   Serial.println("...");
   WiFi.begin(ssid, password);
   int retries = 0;
   while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (retries > 14) {
    Serial.println(F("WiFi connection FAILED"));
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected!"));
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  Serial.println(F("Setup ready"));
}

void setup () {
  Serial.begin(BAUD);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  connect_to_wifi();
  digitalWrite(LED, LOW);
  server.on(
    "/",
    HTTP_GET,
    []() {
      server.send(
        200,
        F("text/html"),
        F("Welcome to the REST Web Server")
      );
    }
  );
  server.on(
    UriBraces("/api/led/{}/colour/{}/{}/{}"),
    HTTP_PUT,
    []() {
      String led = server.pathArg(0);
      String r = server.pathArg(1);
      String g = server.pathArg(2);
      String b = server.pathArg(3);

      StaticJsonDocument<200> doc;

      doc["led"] = led;
      doc["r"] = r;
      doc["g"] = g;
      doc["b"] = b;

      String response = "";
      serializeJson(doc, response);

      server.send(
        200,
        F("application/json"),
        response
      );
    }
  );

  server.on(
    UriBraces("/api/status"),
    HTTP_POST,
    []() {
      digitalWrite(LED, LOW);
      StaticJsonDocument<20> doc;

      doc["status"] = "true";

      String response = "";
      serializeJson(doc, response);

      server.send(
        201,
        F("application/json"),
        response
      );
    }
  );

  server.on(
    UriBraces("/api/status"),
    HTTP_DELETE,
    []() {
      digitalWrite(LED, HIGH);
      StaticJsonDocument<20> doc;

      doc["status"] = "false";

      String response = "";
      serializeJson(doc, response);

      server.send(
        204,
        F("application/json"),
        response
      );
    }
  );

  server.begin();
  digitalWrite(LED, HIGH);
}

void loop () {
  server.handleClient();
}
