#pragma once

#include "deliverable.h"

class Parcel
{
public:
    // Constructor
    Parcel(std::string name, float weight, float length, float width, float depth);

    // Get functions
    float getSize();
    float getPrice();

private:
    // Dimensions
    float length;
    float width;
    float depth;
};