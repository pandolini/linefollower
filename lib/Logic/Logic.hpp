
#ifndef LINEFOLLOWER_LOGIC_HPP
#define LINEFOLLOWER_LOGIC_HPP

#include "Arduino.h"
#include "vector"

class Logic {
private:
    std::vector<std::vector<int8_t>> lookupTableP;
    std::vector<std::vector<int8_t>> lookupTableD;
    int16_t previousPosition;
    int16_t deltaPosition;
    const int16_t deltaOffset = 140;

    int16_t proportional = 0;
    int16_t derivative = 0;
    int8_t output = 0;
    double Kp_;
    double Kd_;

public:
    void initialize();

    int8_t getOutput(uint16_t linePosition);
};

#endif