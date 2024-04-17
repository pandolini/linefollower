
#include "Logic.hpp"
#include "TableLoader.hpp"

Logic::Logic(float outputGain): outputGain_(outputGain) {
    loadTable(&lookupTableP, &lookupTableD);
    previousLinePosition = desiredLinePosition;
}

int16_t Logic::computeCourseCorrection(int16_t currentLinePosition) {
    //Kp_ = (double)lookupTableP[currentLinePosition][deltaPosition(currentLinePosition)]/100;
    //Kd_ = (double)lookupTableD[currentLinePosition][deltaPosition(currentLinePosition)]/100;
    Kp_ = 3.0;
    Kd_ = 6.0;

    proportionalError = currentLinePosition - desiredLinePosition;
    derivativeError = currentLinePosition - previousLinePosition;
    controlOutput = (int)(proportionalError * Kp_) + (derivativeError * Kd_); 
    previousLinePosition = currentLinePosition;
    
    return controlOutput * outputGain_;
}

int16_t Logic::deltaPosition(int16_t currentLinePosition) {
    return constrainDeltaPosition(currentLinePosition - previousLinePosition); //TODO removed deltaOffset, might break fuzzy
}

int16_t Logic::constrainDeltaPosition(int16_t deltaPosition) {
    return deltaPosition < 0 ? 0 : deltaPosition;
}

