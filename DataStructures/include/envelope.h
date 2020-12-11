#pragma once

#include "deliverable.h"

class Envelope {
public:
    
    // Constructor
    Envelope(std::string name, float weight, float length, float width);

    // Get functions
    float getSize();
    float getPrice();

private:

    // Dimensions
    float length;
    float width;
};