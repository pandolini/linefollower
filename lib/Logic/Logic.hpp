
#ifndef LINEFOLLOWER_LOGIC_HPP
#define LINEFOLLOWER_LOGIC_HPP

#include "Arduino.h"
#include "vector"

class Logic {
private:
    std::vector<std::vector<int8_t>> lookupTableP;
    std::vector<std::vector<int8_t>> lookupTableD;
    int16_t lastLinePosition;
    int16_t deltaPosition;
    const int16_t deltaOffset = 140;
    const int16_t desiredLinePosition = 70;
    int16_t proportionalError = 0;
    int16_t derivativeError = 0;
    int16_t controlOutput = 0;
    double Kp_;
    double Kd_;

    int16_t constrainDeltaPosition(int16_t deltaPosition);

public:
    void initialize();

    int16_t computeControlOutput(int16_t currentLinePosition);
};

#endif