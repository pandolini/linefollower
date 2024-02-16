
#include "MotorController.hpp"

MotorController::MotorController(): motor1(MOTOR_A), motor2(MOTOR_B) {

}

void MotorController::throttle(int16_t output) {
    int16_t rightMotorSpeed = constrainSpeed(baseSpeed + output);
    int16_t leftMotorSpeed = constrainSpeed(baseSpeed - output);
    motor1.setmotor(direction(output), rightMotorSpeed);
    motor2.setmotor(direction(-output), leftMotorSpeed);
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

int16_t MotorController::direction(int16_t output) {
    if (output > 0) {
        return FORWARD;
    } else if (output < 0) {
        return BACKWARD;
    } else {
        return STOP;
    }
}