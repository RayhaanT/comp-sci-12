#pragma once

#include "deliverable.h"

class TruckDelivery
{
public:
    // Constructor
    TruckDelivery(std::string name, float weight);

    // Get functions
    float getSize();
    float getPrice();
};