#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include <SparkFun_TB6612.h>

class MotorController {
public:
    MotorController();

    void throttle(int16_t output);

private:
    Motor motor1;
    Motor motor2;
    int16_t constrainSpeed(int16_t speed);

    static const int AIN1 = 95;
    static const int BIN1 = 96;
    static const int AIN2 = 97;
    static const int BIN2 = 98;
    static const int STBY = 99;
    static const int OFFSET = 1;
    static const int PWMA = 0;
    static const int PWMB = 2;

    const int16_t baseSpeed = 100;
    const int16_t maxSpeed = 200;
    const int16_t minSpeed = 0;
};

#endif