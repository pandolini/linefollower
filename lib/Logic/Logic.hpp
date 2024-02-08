
#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Sensor.hpp"
#include "MotorController.hpp"

class Logic {
public:
    Logic();

    void pidControl(uint16_t sensorPosition);

private:
    MotorController motorController;

};

#endif