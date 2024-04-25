
#include "Webserver.hpp"

Webserver::Webserver(const char* ssid, const char* password)
    : ssid_(ssid), password_(password), server_(80) {}

void Webserver::connectWiFi() {
    WiFi.begin(ssid_, password_);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

void Webserver::setupServer(Logic& logic, MotorController& motorController) {
    server_.on("/form", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = R"(
            <form id="paramsForm">
                Kp: <input type="text" name="Kp"><br>
                Kd: <input type="text" name="Kd"><br>
                Ki: <input type="text" name="Ki"><br>
                Base speed: <input type="text" name="baseSpeed"><br>
                Max speed: <input type="text" name="maxSpeed"><br>
                Min speed: <input type="text" name="minSpeed"><br>
                <input type="submit" value="Submit">
            </form>
            <button id="startMotorsButton" style="background-color: green;">Start Motors</button>
            <button id="stopMotorsButton" style="background-color: red;">Stop Motors</button>
            <button id="resetErrorsButton" style="background-color: blue;">Reset Errors</button>
            <script>
                document.getElementById('paramsForm').addEventListener('submit', function(event) {
                    event.preventDefault();
                    var xhr = new XMLHttpRequest();
                    xhr.open('GET', '/set_params?' + new URLSearchParams(new FormData(event.target)).toString(), true);
                    xhr.send();
                });
                document.getElementById('startMotorsButton').addEventListener('click', function() {
                    var xhr = new XMLHttpRequest();
                    xhr.open('GET', '/start_motors', true);
                    xhr.send();
                });
                document.getElementById('stopMotorsButton').addEventListener('click', function() {
                    var xhr = new XMLHttpRequest();
                    xhr.open('GET', '/stop_motors', true);
                    xhr.send();
                });
                document.getElementById('resetErrorsButton').addEventListener('click', function() {
                    var xhr = new XMLHttpRequest();
                    xhr.open('GET', '/reset_errors', true);
                    xhr.send();
                });
            </script>
        )";
        request->send(200, "text/html", html);
    });

    server_.on("/set_params", HTTP_GET, [&logic, &motorController](AsyncWebServerRequest* request) {
        if (request->hasParam("Kp")) {
            logic.setKp(request->getParam("Kp")->value().toFloat());
        }
        if (request->hasParam("Kd")) {
            logic.setKd(request->getParam("Kd")->value().toFloat());
        }
        if (request->hasParam("Ki")) {
            logic.setKi(request->getParam("Ki")->value().toFloat());
        }
        if (request->hasParam("baseSpeed")) {
            motorController.setBaseSpeed(request->getParam("baseSpeed")->value().toFloat());
        }
        if (request->hasParam("maxSpeed")) {
            motorController.setMaxSpeed(request->getParam("maxSpeed")->value().toFloat());
        }
        if (request->hasParam("minSpeed")) {
            motorController.setMinSpeed(request->getParam("minSpeed")->value().toFloat());
        }
        request->send(200, "text/plain", "Parameters set");
    });

    server_.on("/stop_motors", HTTP_GET, [&motorController](AsyncWebServerRequest* request) {
        motorController.disableMotors();
        request->send(200, "text/plain", "Motors stopped");
    });

    server_.on("/start_motors", HTTP_GET, [&motorController](AsyncWebServerRequest* request) {
        motorController.enableMotors();
        request->send(200, "text/plain", "Motors started");
    });

    server_.on("/reset_errors", HTTP_GET, [&logic](AsyncWebServerRequest* request) {
        logic.resetErrors();
        request->send(200, "text/plain", "Error variables reset");
    });

    server_.begin();
}

void Webserver::setupOTA() {
    ArduinoOTA.begin();
}

void Webserver::handleOTA() {
    ArduinoOTA.handle();
}