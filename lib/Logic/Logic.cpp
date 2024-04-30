
#include "Logic.hpp"

Logic::Logic(float Kp, float Kd, float Ki, float outputGain): Kp_(Kp), Kd_(Kd), Ki_(Ki), outputGain_(outputGain), desiredLinePosition_(70) {
    previousLinePosition_ = desiredLinePosition_;
}

short Logic::computeCourseCorrection(unsigned short currentLinePosition) {
    proportionalError_ = currentLinePosition - desiredLinePosition_;
    derivativeError_ = currentLinePosition - previousLinePosition_;
    integralError_ += proportionalError_;
    controlOutput_ = (int) (proportionalError_ * Kp_) + (derivativeError_ * Kd_) + (integralError_ * Ki_);
    previousLinePosition_ = currentLinePosition;

    return controlOutput_ * outputGain_;
}

void Logic::resetErrors() {
    proportionalError_ = 0;
    derivativeError_ = 0;
    integralError_ = 0;
}