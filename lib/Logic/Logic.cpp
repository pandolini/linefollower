
#include "Logic.hpp"
#include "TableLoader.hpp"

void Logic::initialize() {
    loadTable(&lookupTableP, &lookupTableD);
    lastLinePosition = desiredLinePosition;
    deltaPosition = 0;
}

int16_t Logic::computeControlOutput(int16_t currentLinePosition) {
    deltaPosition = constrainDeltaPosition(currentLinePosition - lastLinePosition + deltaOffset);

    //Kp_ = (double)lookupTableP[linePosition][deltaPosition]/100;
    //Kd_ = (double)lookupTableD[linePosition][deltaPosition]/100;
    Kp_ = 1.2;
    Kd_ = 0;

    proportionalError = currentLinePosition - desiredLinePosition;
    derivativeError = currentLinePosition - lastLinePosition;
    controlOutput = (int)(proportionalError * Kp_) + (derivativeError * Kd_); 
    lastLinePosition = currentLinePosition;
    
    return controlOutput;
}

int16_t Logic::constrainDeltaPosition(int16_t deltaPosition) {
    return deltaPosition < 0 ? 0 : deltaPosition;
}