#include <Arduino.h>
#include "vector"
#include "Sensor.hpp"
#include "TableLoader.hpp"

Sensor sensor;
uint16_t linePosition;
std::vector<std::vector<int8_t>> lookupTable;

void setup() {
  TableLoader::load(&lookupTable);
}

void loop() {
  linePosition = sensor.getPos();
}