#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include <Arduino.h>

class MotorController {
public:
    MotorController(int motor_1_pin, int motor_2_pin);

    void throttle(int16_t output);

private:
    int16_t constrainSpeed(int16_t speed);
    void drive(int motor, int16_t speed);

    int motor1;
    int motor2;

    const int16_t baseSpeed = 100;
    const int16_t maxSpeed = 200; // 255 is the absolute maximum
    const int16_t minSpeed = 0;
};

#endif