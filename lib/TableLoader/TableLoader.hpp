
#ifndef LINEFOLLOWER_TABLELOADER_HPP
#define LINEFOLLOWER_TABLELOADER_HPP

#include "Arduino.h"
#include "SPIFFS.h"
#include "vector"

void loadTable(std::vector<std::vector<int8_t>>* table) {
    if (!SPIFFS.begin()) {
        Serial.print("Error starting LittleFS");
        return;
    }

    File file = SPIFFS.open("/table.csv");
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