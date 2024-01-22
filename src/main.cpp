#include <Arduino.h>
#include <Wire.h>
#include <QTRSensors.h>
#include "WemosMotorShieldESP32.h"
#include "esp_log.h"


//// Motor driver init
WemosMotorShield motorController(I2C_NUM_0);
// Sensor init
QTRSensors qtr;
const uint8_t SensorCount = 17;
uint16_t sensorValues[SensorCount];

void calibrationSequence() { // Calibration function

    // Setup I2C
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



    pinMode(2, INPUT); // Sensor PINS
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(12, INPUT);
    pinMode(13, INPUT);
    pinMode(14, INPUT);
    pinMode(15, INPUT);
    pinMode(16, INPUT);
    pinMode(17, INPUT);
    pinMode(18, INPUT);
    pinMode(19, INPUT);
    pinMode(23, INPUT);
    pinMode(25, INPUT);
    pinMode(26, INPUT);
    pinMode(27, INPUT);
    pinMode(32, INPUT);
    pinMode(33, INPUT);

    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]) {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 23, 25, 26, 27, 32, 33}, SensorCount);
    delay(500);

    for (uint16_t i = 0; i < 400; i++) // Calibration loop (400 iterations)
    {
        qtr.calibrate();
    }
}

void throttle(int16_t output) { // Throttle function

    const int16_t baseSpeed = 50; // Base speed of the motors
    const int16_t maxSpeed = 100; // Maximum speed of the motors
    const int16_t minSpeed = 0; // Minimum speed of the motors
    int16_t rightMotorSpeed = baseSpeed + output; // Calculates motor speed
    int16_t leftMotorSpeed = baseSpeed - output;
    if (rightMotorSpeed > maxSpeed) { // Limits the motor speed
        rightMotorSpeed = maxSpeed;
    }
    if (rightMotorSpeed < minSpeed) {
        rightMotorSpeed = minSpeed;
    }
    if (leftMotorSpeed > maxSpeed) {
        leftMotorSpeed = maxSpeed;
    }
    if (leftMotorSpeed < minSpeed) {
        leftMotorSpeed = minSpeed;
    }
    motorController.setMotor(MOTOR_A, FORWARD, rightMotorSpeed); // Drives the motors
    motorController.setMotor(MOTOR_B, BACKWARD, leftMotorSpeed); // Drives the motors
}

void pidControl() { // PID algorithm
    uint16_t position = qtr.readLineBlack(sensorValues); // Reads sensor values and calculates the position
    int16_t error = position - 5500; // 5500 is the middle of the sensor array
    int16_t proportional = 0;
    int16_t integral = 0;
    int16_t derivative = 0;
    int16_t lastError = 0;
    int16_t output = 0;
    const double Kp = 0.10000; // PID constants ********TO BE TUNED********
    const double Ki = 0.00000;
    const double Kd = 0.02500;

    while (true) { // PID loop
        proportional = error;
        integral += error;
        derivative = error - lastError;
        output = (proportional * Kp) + (integral * Ki) + (derivative * Kd); // PID equation
        lastError = error;
        position = qtr.readLineBlack(sensorValues); // Reads sensor values and updates the position
        error = position - 5500;
        throttle(output); // Throttles the motors
    }
}

void setup() {
    calibrationSequence();
}

void loop() {
    pidControl();
}