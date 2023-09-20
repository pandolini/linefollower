#include <Arduino.h>
#include <QTRSensors.h>
#include <SparkFun_TB6612.h>

// Motor driver init
#define AIN1 8 // Motor PINS
#define BIN1 12
#define AIN2 9
#define BIN2 13
#define PWMA 10
#define PWMB 11
#define STBY 99
const int offsetA = 1;
const int offsetB = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

// Sensor init
QTRSensors qtr;
const uint8_t SensorCount = 12;
uint16_t sensorValues[SensorCount];

void calibrationSequence() { // Calibration function
    pinMode(A0, INPUT); // Sensor PINS (It is needed for analog pins to work as digital)
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, 2, 3, 4, 5, 6, 7}, SensorCount);

    for (uint16_t i = 0; i < 400; i++) // Calibration loop (400 iterations)
    {
        qtr.calibrate();
    }
}

void throttle(int16_t output) { // Throttle function
    const int16_t baseSpeed = 50; // Base speed of the motors
    const int16_t maxSpeed = 100; // Maximum speed of the motors
    const int16_t minSpeed = -100; // Minimum speed of the motors
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
    motor1.drive(rightMotorSpeed); // Drives the motors
    motor2.drive(rightMotorSpeed);
}

void pidControl() { // PID algorithm
        uint16_t position = qtr.readLineBlack(sensorValues); // Reads sensor values and calculates the position
        int16_t error = position - 6000; // 6000 is the middle of the sensor array
        int16_t proportional = 0;
        int16_t integral = 0;
        int16_t derivative = 0;
        int16_t lastError = 0;
        int16_t output = 0;
        const float Kp = 0.2; // PID constants ********TO BE TUNED********
        const float Ki = 0.2;
        const float Kd = 0.2;

        while (true) { // PID loop
            proportional = error;
            integral += error;
            derivative = error - lastError;
            output = (proportional * Kp) + (integral * Ki) + (derivative * Kd); // PID equation
            lastError = error;
            position = qtr.readLineBlack(sensorValues); // Reads sensor values and updates the position
            error = position - 6000;
            throttle(output); // Throttles the motors
        }
}

int main() {
    calibrationSequence();
    pidControl();
    return 0;
}