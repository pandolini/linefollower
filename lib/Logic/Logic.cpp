
#include "Logic.hpp"
#include "TableLoader.hpp"

Logic::Logic(double Kp, double Kd, double Ki, float outputGain): Kp_(Kp), Kd_(Kd), Ki_(Ki), outputGain_(outputGain) {
    previousLinePosition = desiredLinePosition;
}

int16_t Logic::computeCourseCorrection(int16_t currentLinePosition) {
    proportionalError = currentLinePosition - desiredLinePosition;
    derivativeError = currentLinePosition - previousLinePosition;
    integralError += proportionalError;
    controlOutput = (int) (proportionalError * Kp_) + (derivativeError * Kd_) + (integralError * Ki_);
    previousLinePosition = currentLinePosition;

    return controlOutput * outputGain_;
}

int16_t Logic::deltaPosition(int16_t currentLinePosition) {
    return constrainDeltaPosition(currentLinePosition - previousLinePosition + deltaOffset);
}

int16_t Logic::constrainDeltaPosition(int16_t deltaPosition) {
    return deltaPosition < 0 ? 0 : deltaPosition;
}

void Logic::updateDesiredLineposition(int16_t currentLinePosition) {
    if (currentLinePosition < 50) {
        desiredLinePosition = 50 + (70 - 50) * ((currentLinePosition - 50) / 20.0);
    } else if (currentLinePosition > 90) {
        desiredLinePosition = 70 + (90 - 70) * ((currentLinePosition - 90) / 20.0);
    } else {
        desiredLinePosition = 70;
    }
}

void Logic::resetErrors() {
    proportionalError = 0;
    derivativeError = 0;
    integralError = 0;
}

void Logic::initializeFuzzylogic() {
    loadTable(&lookupTableP, &lookupTableD);
}

void Logic::updateFuzzyParameters(int16_t currentLinePosition) {
    setKp((double) lookupTableP[currentLinePosition][deltaPosition(currentLinePosition)] / 100);
    setKd((double) lookupTableD[currentLinePosition][deltaPosition(currentLinePosition)] / 100);
}

void Logic::setKp(double Kp) {
    Kp_ = Kp;
}

void Logic::setKd(double Kd) {
    Kd_ = Kd;
}

void Logic::setKi(double Ki) {
    Ki_ = Ki;
}

double Logic::getKp() const {
    return Kp_;
}

double Logic::getKd() const {
    return Kd_;
}

double Logic::getKi() const {
    return Ki_;
}