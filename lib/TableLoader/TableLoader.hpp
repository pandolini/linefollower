
#ifndef LINEFOLLOWER_TABLELOADER_HPP
#define LINEFOLLOWER_TABLELOADER_HPP

#include "Arduino.h"
#include "SPIFFS.h"
#include "vector"

void loadTable(std::vector<std::vector<int8_t>>* tableP, std::vector<std::vector<int8_t>>* tableD) {
    if (!SPIFFS.begin()) {
        Serial.println("Error starting LittleFS");
        return;
    }

    loadFile("/tableP.csv", tableP);
    loadFile("/tableD.csv", tableD);
}

void loadFile(std::string fileName, std::vector<std::vector<int8_t>>* table) {
    File file = SPIFFS.open(fileName.c_str());
    if (!file) {
        Serial.println("Error loading table.csv");
        return;
    }

    while (file.available()) {
        std::vector<int8_t> row;
        auto line = file.readStringUntil(13);
        while (line.length() >= 3) {
            auto index = line.indexOf(',');
            if (index == -1) {
                row.push_back(line.toInt());
                break;
            }
            auto value = line.substring(0, index);
            line.remove(0, index + 1);
            row.push_back(value.toInt());
        }
        table->push_back(row);
    }
    file.close();
}

#endif