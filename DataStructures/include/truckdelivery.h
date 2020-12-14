#pragma once

#include "deliverable.h"

#define TRUCK_OVERSIZE_WEIGHT 100
#define TRUCK_PRICE_PER_KILO 1.20f
#define TRUCK_BASE_PRICE 50

/**
 * The child class to handle special truck deliveries.
 * Prices are based on weight.
*/
class TruckDelivery : public Deliverable
{
public:
    // Constructor
    TruckDelivery(std::string name, float weight);

    // Get functions
    float getSize() override;
    float getPrice() override;
};