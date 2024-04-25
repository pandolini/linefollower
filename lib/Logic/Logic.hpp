
#ifndef LINEFOLLOWER_LOGIC_HPP
#define LINEFOLLOWER_LOGIC_HPP

#include "Arduino.h"
#include "vector"

class Logic {
public:
    Logic(double Kp, double Kd, double Ki, float outputGain);
    int16_t computeCourseCorrection(int16_t currentLinePosition);
    int16_t deltaPosition(int16_t currentLinePosition);
    void updateDesiredLineposition(int16_t currentLinePosition);
    void resetErrors();

    void initializeFuzzylogic();
    void updateFuzzyParameters(int16_t currentLinePosition);

    void setKp(double Kp);
    void setKd(double Kd);
    void setKi(double Ki);

private:
    std::vector<std::vector<int8_t>> lookupTableP;
    std::vector<std::vector<int8_t>> lookupTableD;
    int16_t previousLinePosition;
    const int16_t deltaOffset = 140;
    int16_t desiredLinePosition = 70;
    double proportionalError = 0;
    double derivativeError = 0;
    double integralError = 0;
    int16_t controlOutput = 0;
    double Kp_;
    double Kd_;
    double Ki_;
    float outputGain_;


    int16_t constrainDeltaPosition(int16_t deltaPosition);
};

#endif