#include "envelope.h"

Envelope::Envelope(std::string name, float weight, float length, float width) : Deliverable() {
    this->name = name;
    this->weight = weight;
    this->length = length;
    this->width = width;
    this->orderType = "Envelope";
}

float Envelope::getSize() {
    return length*width*MAX_ENVELOPE_DEPTH;
}

float Envelope::getPrice() {
    float size = getSize();
    float extra = 0;
    if(size > 22*11) {
        extra = (size - 22 * 11) * ENV_PRICE_PER_SQ_CM;
    }
    return ENV_PRICE_FOR_REGULAR_SIZE + extra;
}