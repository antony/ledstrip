#include <ESP8266WebServer.h>

void health_handlers (ESP8266WebServer& server) {
  server.on(
    "/",
    HTTP_GET,
    [&server]() {
      server.send(
        200,
        F("text/html"),
        F("Welcome to the REST Web Server")
      );
    }
  );
}
