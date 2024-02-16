
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include <Wire.h>

#define MOTOR_A 0
#define MOTOR_B 1

#define BRAKE 0
#define BACKWARD 1
#define FORWARD 2
#define STOP 3
#define STANDBY 4

class Motor {
public:
    Motor(uint8_t motor, uint32_t frequency);
    void setfrequency(uint32_t frequency);
	void setmotor(uint8_t operation, float pwm_value);

private:
    uint8_t _address;
    uint8_t _motor;
};

#endif