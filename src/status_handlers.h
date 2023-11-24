#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <uri/UriBraces.h>

#define LED D4

void status_handlers (ESP8266WebServer& server) {
  server.on(
    UriBraces("/api/status"),
    HTTP_POST,
    [&server]() {
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
    [&server]() {
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
}
