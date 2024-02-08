
#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "MotorController.hpp"

class Logic {
public:
    Logic(double Kp, double Ki, double Kd);

    void pidControl(uint16_t sensorPosition);

private:
    MotorController motorController;

    uint16_t position = 0;
    int16_t error = 0;
    int16_t lastError = 0;
    int16_t proportional = 0;
    int16_t integral = 0;
    int16_t derivative = 0;
    int16_t output = 0;
    double Kp_;
    double Ki_;
    double Kd_;
};

#endif