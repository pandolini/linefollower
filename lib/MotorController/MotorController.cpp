
#include "MotorController.hpp"

MotorController::MotorController(int motor_1_pin, int motor_2_pin): motor1(motor_1_pin), motor2(motor_2_pin){}

void MotorController::throttle(int16_t output) {
    int16_t rightMotorSpeed = constrainSpeed(baseSpeed + output);
    int16_t leftMotorSpeed = constrainSpeed(baseSpeed - output);
    drive(motor1, rightMotorSpeed);
    drive(motor2, leftMotorSpeed);
}

int16_t MotorController::constrainSpeed(int16_t speed) {
    if (speed > maxSpeed) {
        return maxSpeed;
    } else if (speed < minSpeed) {
        return minSpeed;
    } else {
        return speed;
    }
}

void MotorController::drive(int motor, int16_t speed) {
    analogWrite(motor, speed);
}