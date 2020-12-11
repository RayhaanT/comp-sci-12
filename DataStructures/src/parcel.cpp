#include "parcel.h"

Parcel::Parcel(std::string name, float weight, float length, float width, float depth) : Deliverable(){
    
    this->name = name;
    this->weight = weight;
    this->length = length;
    this->width = width;
    this->depth = depth;
}

float Parcel::getSize() {
    return length*width*depth;
}

float Parcel::getPrice() {
    float weightTerm = weight * PARCEL_PRICE_PER_KILO;
    float sizeTerm = getSize() * PARCEL_PRICE_PER_CUBIC_CM;
    return weightTerm + sizeTerm;
}