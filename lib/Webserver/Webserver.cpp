
#include "Webserver.hpp"
#include <FS.h>
#include <SPIFFS.h>

Webserver::Webserver(const char* ssid, const char* password)
    : ssid_(ssid), password_(password), server_(80) {
    SPIFFS.begin();
}

void Webserver::connectWiFi() {
    WiFi.begin(ssid_, password_);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

void Webserver::setupServer(Logic& logic, MotorController& motorController) {
    server_.on("/form", HTTP_GET, [&logic, &motorController](AsyncWebServerRequest* request) {
        String html = R"(
        <form id="paramsForm">
            Kp: <input type="text" name="Kp" value=")" +
                      String(logic.getKp()) + R"("><br>
            Kd: <input type="text" name="Kd" value=")" +
                      String(logic.getKd()) + R"("><br>
            Ki: <input type="text" name="Ki" value=")" +
                      String(logic.getKi()) + R"("><br>
            Base speed: <input type="text" name="baseSpeed" value=")" +
                      String(motorController.getBaseSpeed()) + R"("><br>
            Max speed: <input type="text" name="maxSpeed" value=")" +
                      String(motorController.getMaxSpeed()) + R"("><br>
            Min speed: <input type="text" name="minSpeed" value=")" +
                      String(motorController.getMinSpeed()) + R"("><br>
            Time: <input type="text" id="time" name="time" value=""><br>
            <input type="submit" value="Submit">
            <button id="saveButton">Save</button>
            <button id="downloadButton">Download</button>
            <button id="purgeLogButton">Purge Log Files</button>
            <button id="purgeMasterLogButton">Purge Master Log File</button>
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
            document.getElementById('saveButton').addEventListener('click', function() {
                var xhr = new XMLHttpRequest();
                xhr.open('GET', '/save_params?' + new URLSearchParams(new FormData(document.getElementById('paramsForm'))).toString(), true);
                xhr.send();
            });
            document.getElementById('downloadButton').addEventListener('click', function() {
                var time = document.getElementById('time').value;
                window.location.href = '/get_file?time=' + time;
            });
            document.getElementById('purgeLogButton').addEventListener('click', function() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', '/purge_log', true);
            xhr.send();
            });
            document.getElementById('purgeMasterLogButton').addEventListener('click', function() {
                var xhr = new XMLHttpRequest();
                xhr.open('GET', '/purge_master_log', true);
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

    server_.on("/get_params", HTTP_GET, [&logic, &motorController](AsyncWebServerRequest* request) {
        String json = "{";
        json += "\"Kp\":" + String(logic.getKp()) + ",";
        json += "\"Kd\":" + String(logic.getKd()) + ",";
        json += "\"Ki\":" + String(logic.getKi()) + ",";
        json += "\"baseSpeed\":" + String(motorController.getBaseSpeed()) + ",";
        json += "\"maxSpeed\":" + String(motorController.getMaxSpeed()) + ",";
        json += "\"minSpeed\":" + String(motorController.getMinSpeed());
        json += "}";
        request->send(200, "application/json", json);
    });

    server_.on("/save_params", HTTP_GET, [&logic, &motorController](AsyncWebServerRequest* request) {
        String time = request->getParam("time")->value();
        String filename = "/test_log_" + time + ".txt";
        String masterFilename = "/test_log_master.txt";
        File fileList = SPIFFS.open("/file_list.txt", "a");
            if (!fileList) {
                request->send(500, "text/plain", "Failed to open file list for writing");
                return;
            }
            fileList.println(filename);
            fileList.close();
        File file = SPIFFS.open(filename, "w");
        File masterFile = SPIFFS.open(masterFilename, "a");
        if (!file || !masterFile) {
            request->send(500, "text/plain", "Failed to open file for writing");
            return;
        }
        String log = "Time: " + time + "\n\n"
                    + "Kp: " + String(logic.getKp()) + "\n"
                    + "Kd: " + String(logic.getKd()) + "\n"
                    + "Ki: " + String(logic.getKi()) + "\n"
                    + "Base speed: " + String(motorController.getBaseSpeed()) + "\n"
                    + "Max speed: " + String(motorController.getMaxSpeed()) + "\n"
                    + "Min speed: " + String(motorController.getMinSpeed()) + "\n\n";
        file.print(log);
        masterFile.print(log);
        file.close();
        masterFile.close();
        request->send(200);
    });

    server_.on("/get_file", HTTP_GET, [](AsyncWebServerRequest* request) {
        String time = request->getParam("time")->value();
        String filename = "/test_log_" + time + ".txt";
        if (SPIFFS.exists(filename)) {
            request->send(SPIFFS, filename, "application/octet-stream");
        } else {
            request->send(404, "text/plain", "File not found");
        }
    });

    server_.on("/purge_log", HTTP_GET, [](AsyncWebServerRequest* request) {
        File fileList = SPIFFS.open("/file_list.txt", "r");
        if (!fileList) {
            request->send(500, "text/plain", "Failed to open file list for reading");
            return;
        }
        while (fileList.available()) {
            String filename = fileList.readStringUntil('\n');
            filename.trim();
            if (!SPIFFS.remove(filename)) {
                request->send(500, "text/plain", "Failed to purge log file: " + filename);
                return;
            }
        }
        fileList.close();
        SPIFFS.remove("/file_list.txt");
        request->send(200, "text/plain", "Log files purged successfully");
    });

    server_.on("/purge_master_log", HTTP_GET, [](AsyncWebServerRequest* request) {
        String masterFilename = "/test_log_master.txt";
        if (!SPIFFS.remove(masterFilename)) {
            request->send(500, "text/plain", "Failed to purge master log file");
            return;
        }
        request->send(200, "text/plain", "Master log file purged successfully");
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