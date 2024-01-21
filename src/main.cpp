#include "Arduino.h"
#include "vector"
#include "Sensor.hpp"
#include "Logic.hpp"

Sensor sensor;
Logic logic;
uint16_t linePosition;

void setup() {
  sensor.initialize();
  logic.initialize();
}

void loop() {
  linePosition = sensor.getPos();
  auto output = logic.getOutput(linePosition);
}