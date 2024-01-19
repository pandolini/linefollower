#include "TableLoader.hpp"
#include "LittleFS.h"

void TableLoader::load(std::vector<std::vector<int8_t>>* table) {
    if (!LittleFS.begin()) {
        return;
    }

    File file = LittleFS.open("/table.csv");
    if (!file){
        return;
    }

    while (file.available()) {
        std::vector<int8_t> row;
        auto line = file.readStringUntil(13);
        if (line == NULL) {
            line = file.readStringUntil('\n');
            if (line == NULL) {
                break;
            }
        }
        while (line.length() != 0) {
            auto index = line.indexOf(',');
            if (index == -1) {
                row.push_back(line.toInt());
                return;
            }
            auto value = line.substring(0, index);
            line.remove(0, index+1);
            row.push_back(value.toInt());
        }
        table->push_back(row);
    }
}