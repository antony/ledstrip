#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <uri/UriBraces.h>

void led_handlers (ESP8266WebServer& server) {
  server.on(
    UriBraces("/api/led/{}/colour/{}/{}/{}"),
    HTTP_PUT,
    [&server]() {
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
}
