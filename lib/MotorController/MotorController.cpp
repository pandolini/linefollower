
#include "MotorController.hpp"

MotorController::MotorController(): motorShield(I2C_NUM_0){
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_NUM_21;
    conf.scl_io_num = GPIO_NUM_22;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    i2c_set_timeout(I2C_NUM_0, 30000);
}

void MotorController::throttle(int16_t output) {
    int16_t rightMotorSpeed = constrainSpeed(baseSpeed + output);
    int16_t leftMotorSpeed = constrainSpeed(baseSpeed - output);
    drive(MOTOR_A, FORWARD, rightMotorSpeed);
    drive(MOTOR_B, FORWARD, leftMotorSpeed);
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

void MotorController::drive(motor_num_t motor, MotorDirection direction, int16_t speed) {
    motorShield.setMotor(motor, direction, speed);
}