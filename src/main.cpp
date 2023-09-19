#include <Arduino.h>
#include <QTRSensors.h>
#include <SparkFun_TB6612.h>

#define AIN1 8 // Motor PINS
#define BIN1 12
#define AIN2 9
#define BIN2 13
#define PWMA 10
#define PWMB 11
#define STBY 99

const int offsetA = 1; // Motor init
const int offsetB = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


QTRSensors qtr; // Sensor init
const uint8_t SensorCount = 12;
uint16_t sensorValues[SensorCount];

void setup()
{
    pinMode(A0, INPUT); // Sensor PINS
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
//  delay(500);
// pinMode(LED_BUILTIN, OUTPUT);
// digitalWrite(LED_BUILTIN, HIGH);

    for (uint16_t i = 0; i < 400; i++) // Calibration loop (400 iterations)
    {
        qtr.calibrate();
    }
// digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);

    for (uint8_t i = 0; i < SensorCount; i++) // Prints minimum values from calibration loop
    {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    for (uint8_t i = 0; i < SensorCount; i++) // Prints maximum values from calibration loop
    {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
//  delay(1000);
}

uint16_t linePosition() { // Reads sensor values and returns position

    uint16_t position = qtr.readLineBlack(sensorValues);

    for (uint8_t i = 0; i < SensorCount; i++) // Prints sensor values
    {
        Serial.print(sensorValues[i]);
        Serial.print('\t');
    }
    Serial.println(position);
//  delay(250);
    return position;
}

void linefollow() { // Line following algorithm

    if (5000 < linePosition() and linePosition() < 8000) { // If line is in the middle, go straight
        forward(motor1, motor2, 50);
    }
    else if (linePosition() > 9000) { // If line is on the right, turn left
        motor2.drive(-25);
        motor1.drive(50);
    }
    else if (linePosition() < 4000) { // If line is on the left, turn right
        motor2.drive(50);
        motor1.drive(-25);
    }
    else { // If line is lost, stop
        brake(motor1, motor2);
    }
}

void loop() {
    linePosition();
    linefollow();
}