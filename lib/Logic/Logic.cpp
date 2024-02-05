
#include "Logic.hpp"
#include "TableLoader.hpp"

void Logic::initialize() {
    loadTable(&lookupTable);
    previousPosition = 120;
    deltaPosition = 0;
}

int8_t Logic::getOutput(uint16_t linePosition) {
    deltaPosition = linePosition - previousPosition + deltaOffset;
    if (deltaPosition < 0) {
        deltaPosition = 0;
    }
    previousPosition = linePosition;
    return lookupTable[linePosition][deltaPosition];
}
