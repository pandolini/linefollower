
#include "Motor.hpp"

Motor::Motor(uint8_t motor) {
    if (motor == MOTOR_A)
        _motor = MOTOR_A;
    else
        _motor = MOTOR_B;
    Wire.begin();
    _address = 0x30;
}

void Motor::setmotor(uint8_t operation, float pwm_value) {

    uint16_t _pwm_value;

    Wire.beginTransmission(_address);
    Wire.write(_motor | (byte) 0x10);
    Wire.write(operation);

    _pwm_value = uint16_t(pwm_value * 100);

    if (_pwm_value > 10000)
        _pwm_value = 10000;

    Wire.write((byte) (_pwm_value >> 8));
    Wire.write((byte) _pwm_value);
    Wire.endTransmission();
    delay(100);
}