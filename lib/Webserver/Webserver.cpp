
#include "Webserver.hpp"

Webserver::Webserver(const char* ssid, const char* password)
    : ssid_(ssid), password_(password), server_(80) {}

void Webserver::connectWiFi() {
    WiFi.begin(ssid_, password_);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

void Webserver::setupServer(Logic& logic) {
    server_.on("/set_pid", HTTP_GET, [&logic](AsyncWebServerRequest* request) {
        if (request->hasParam("Kp")) {
            logic.setKp(request->getParam("Kp")->value().toFloat());
        }
        if (request->hasParam("Kd")) {
            logic.setKd(request->getParam("Kd")->value().toFloat());
        }
        if (request->hasParam("Ki")) {
            logic.setKi(request->getParam("Ki")->value().toFloat());
        }
        request->send(200, "text/plain", "OK, ready to recieve new parameters.");
    });

    server_.begin();
}

void Webserver::setupOTA() {
    ArduinoOTA.begin();
}

void Webserver::handleOTA() {
    ArduinoOTA.handle();
}