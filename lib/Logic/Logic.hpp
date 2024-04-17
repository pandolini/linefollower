
#ifndef LINEFOLLOWER_LOGIC_HPP
#define LINEFOLLOWER_LOGIC_HPP

#include "Arduino.h"
#include "vector"

class Logic {
public:
    Logic(float outputGain);
    int16_t computeCourseCorrection(int16_t currentLinePosition);
    int16_t deltaPosition(int16_t currentLinePosition);

private:
    std::vector<std::vector<int8_t>> lookupTableP;
    std::vector<std::vector<int8_t>> lookupTableD;
    int16_t previousLinePosition;
    const int16_t deltaOffset = 140;
    const int16_t desiredLinePosition = 70;
    int16_t proportionalError = 0;
    int16_t derivativeError = 0;
    int16_t controlOutput = 0;
    double Kp_;
    double Kd_;
    float outputGain_;
    int16_t constrainDeltaPosition(int16_t deltaPosition);
};

#endif