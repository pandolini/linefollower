
#include "Motor.hpp"

Motor::Motor(uint8_t motor, uint32_t frequency) {
    Wire.begin();
    if (motor == MOTOR_A)
        _motor = MOTOR_A;
    else
        _motor = MOTOR_B;
    _address = 0x30;
    setfrequency(frequency);
}

void Motor::setfrequency(uint32_t frequency) {
    Wire.beginTransmission(_address);
    Wire.write(((byte) (frequency >> 16)) & (byte) 0x0f);
    Wire.write((byte) (frequency >> 16));
    Wire.write((byte) (frequency >> 8));
    Wire.write((byte) frequency);
    Wire.endTransmission();
    delay(100);
}

void Motor::setmotor(uint8_t dir, float pwm_value) {
    uint16_t _pwm_value;

    Wire.beginTransmission(_address);
    Wire.write(_motor | (byte) 0x10);
    Wire.write(dir);

    _pwm_value = uint16_t(pwm_value * 100);

    if (_pwm_value > 10000)
        _pwm_value = 10000;

    Wire.write((byte) (_pwm_value >> 8));
    Wire.write((byte) _pwm_value);
    Wire.endTransmission();
    delay(100);
}