#pragma once

#include "deliverable.h"

#define ENVELOPE_DEPTH 0.1f;
#define ENV_PRICE_FOR_REGULAR_SIZE 2.0f // Price for regular 11cmx22cm envelope
#define ENV_PRICE_PER_SQ_CM 0.01 // For oversized envelopes

class Envelope : Deliverable {
public:
    
    // Constructor
    Envelope(std::string name, float weight, float length, float width);

    // Get functions
    float getSize() override;
    float getPrice() override;

private:

    // Dimensions
    float length;
    float width;
};