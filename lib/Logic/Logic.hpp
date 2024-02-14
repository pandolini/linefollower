
#ifndef LINEFOLLOWER_LOGIC_HPP
#define LINEFOLLOWER_LOGIC_HPP

#include "Arduino.h"
#include "vector"

class Logic {
private:
    std::vector<std::vector<int8_t>> lookupTable;
    int16_t previousPosition;
    int16_t deltaPosition;
    const int16_t deltaOffset = 140;

public:
    void initialize();

    int8_t getOutput(uint16_t linePosition);
};

#endif