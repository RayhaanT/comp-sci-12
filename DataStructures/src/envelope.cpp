#include "envelope.h"

/**
 * This is the constructor function for new envelope delivery objects
 * 
 * @param name - The order name
 * @param weight - The weight of the object being delivered
 * @param length - The object's length
 * @param width - The object's width
 * 
*/
Envelope::Envelope(std::string name, float weight, float length, float width) : Deliverable() {
    this->name = name;
    this->weight = weight;
    this->length = length;
    this->width = width;
    this->orderType = "Envelope";
}

/**
 * A virtual override to calculate the envelope's volume
 * 
 * @return the volume in cubic centimeters
 * 
*/
float Envelope::getSize() {
    return length*width*MAX_ENVELOPE_DEPTH;
}

/**
 * A virtual override to calculate the delivery price based on size
 * 
 * @return the price of the envelope delivery
 * 
*/
float Envelope::getPrice() {
    float size = getSize();
    float extra = 0;
    if(size > 22*11) {
        extra = (size - 22 * 11) * ENV_PRICE_PER_SQ_CM;
    }
    return ENV_PRICE_FOR_REGULAR_SIZE + extra;
}