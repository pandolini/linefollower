#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include <Arduino.h>
#include "Motor.hpp"

class MotorController {
public:
    MotorController();

    void throttle(int16_t output);

private:
    int16_t constrainSpeed(int16_t speed);
    int16_t direction(int16_t output);

    Motor motor1;
    Motor motor2;

    const int16_t baseSpeed = 75;
    const int16_t maxSpeed = 100; // 255 is the absolute maximum
    const int16_t minSpeed = -100;
};

#endif