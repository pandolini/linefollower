#include <Arduino.h>
#include "../lib/Sensor/Sensor.hpp"

Sensor sensor;
int16_t linePosition;
void setup() {

}

void loop() {
  linePosition = sensor.getPos();
}