
#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include "Logic.hpp"

class Webserver {

public:
    Webserver(const char* ssid, const char* password);

    void connectWiFi();
    void setupServer(Logic& logic);
    void setupOTA();
    void handleOTA();

private:
    const char* ssid_;
    const char* password_;
    AsyncWebServer server_;
};

#endif