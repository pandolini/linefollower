#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include <Arduino.h>
#include "WemosMotorShieldESP32.h"
#include "esp_log.h"

class MotorController {
public:
    MotorController();

    void throttle(int16_t output);

private:
    int16_t constrainSpeed(int16_t speed);
    void drive(motor_num_t motor, MotorDirection direction, int16_t speed);

    WemosMotorShield motorShield;

    const int16_t baseSpeed = 100;
    const int16_t maxSpeed = 200; // 255 is the absolute maximum
    const int16_t minSpeed = 0;
};

#endif