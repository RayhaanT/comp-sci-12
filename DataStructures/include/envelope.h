#pragma once

#include "deliverable.h"

#define MAX_ENVELOPE_DEPTH 2;
#define ENV_PRICE_FOR_REGULAR_SIZE 2.0f // Price for regular 11cmx22cm envelope
#define ENV_PRICE_PER_SQ_CM 0.01 // For oversized envelopes

class Envelope : public Deliverable {
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