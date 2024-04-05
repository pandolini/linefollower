
#include "Logic.hpp"
#include "TableLoader.hpp"

void Logic::initialize() {
    loadTable(&lookupTableP, &lookupTableD);
    previousPosition = 70;
    deltaPosition = 0;
}

int8_t Logic::getOutput(uint16_t linePosition) {
    deltaPosition = linePosition - previousPosition + deltaOffset;
    if (deltaPosition < 0) {
        deltaPosition = 0;
    }

    Kp_ = (double)lookupTableP[linePosition][deltaPosition]/100;
    Kd_ = (double)lookupTableD[linePosition][deltaPosition]/100;

    proportional = linePosition - 70;
    derivative = linePosition - previousPosition;
    output = (proportional * Kp_) + (derivative * Kd_);
    
    previousPosition = linePosition;
    
    return output;
}
