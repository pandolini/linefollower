#ifndef LINEFOLLOWER_TABLELOADER_HPP
#define LINEFOLLOWER_TABLELOADER_HPP

#include "Arduino.h"
#include "vector"

class TableLoader
{
public:
    static void load(std::vector<std::vector<int8_t>>* table);
};

#endif