
#include "Logic.hpp"
#include "TableLoader.hpp"

void Logic::initialize() {
    loadTable(&lookupTableP, &lookupTableD);
    previousPosition = 70;
    deltaPosition = 0;
}

int16_t Logic::getOutput(int16_t linePosition) {
    deltaPosition = linePosition - previousPosition + deltaOffset;
    if (deltaPosition < 0) {
        deltaPosition = 0;
    }

    //Kp_ = (double)lookupTableP[linePosition][deltaPosition]/100;
    //Kd_ = (double)lookupTableD[linePosition][deltaPosition]/100;
    Kp_ = 1.2;
    Kd_ = 0;

    proportional = linePosition - 70;
    derivative = linePosition - previousPosition;
    output = (int)(proportional * Kp_) + (derivative * Kd_);
    
    previousPosition = linePosition;
    
    return output;
}
