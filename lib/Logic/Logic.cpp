
#include "Logic.hpp"
#include "TableLoader.hpp"

Logic::Logic(float outputGain): outputGain_(outputGain) {
    previousLinePosition = desiredLinePosition;
}

void Logic::initializeFuzzylogic() {
    loadTable(&lookupTableP, &lookupTableD);
}

int16_t Logic::computeCourseCorrection(int16_t currentLinePosition) {
    //Kp_ = (double)lookupTableP[currentLinePosition][deltaPosition(currentLinePosition)]/100;
    //Kd_ = (double)lookupTableD[currentLinePosition][deltaPosition(currentLinePosition)]/100;
    Kp_ = 4.5;
    Kd_ = 6.5;

    proportionalError = currentLinePosition - desiredLinePosition;
    derivativeError = currentLinePosition - previousLinePosition;
    controlOutput = (int)(proportionalError * Kp_) + (derivativeError * Kd_); 
    previousLinePosition = currentLinePosition;
    
    return controlOutput * outputGain_;
}

int16_t Logic::deltaPosition(int16_t currentLinePosition) {
    return constrainDeltaPosition(currentLinePosition - previousLinePosition + deltaOffset);
}

int16_t Logic::constrainDeltaPosition(int16_t deltaPosition) {
    return deltaPosition < 0 ? 0 : deltaPosition;
}

