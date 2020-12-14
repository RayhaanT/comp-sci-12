#pragma once

#include "deliverable.h"

#define PARCEL_PRICE_PER_KILO 1.20
#define PARCEL_PRICE_PER_CUBIC_CM 0.001

/**
 * The child class to handle parcel deliveries.
 * Prices are based on weight and volume.
*/
class Parcel : public Deliverable {
public:
    // Constructor
    Parcel(std::string name, float weight, float length, float width, float depth);

    // Get functions
    float getSize() override;
    float getPrice() override;

private:
    // Dimensions
    float length;
    float width;
    float depth;
};