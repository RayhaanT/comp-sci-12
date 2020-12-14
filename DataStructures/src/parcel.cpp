#include "parcel.h"

/**
 * This is the constructor function for new parcel delivery objects
 * 
 * @param name - The order name
 * @param weight - The weight of the object being delivered
 * @param length - The object's length
 * @param width - The object's width
 * @param depth - The object's depth
 * 
*/
Parcel::Parcel(std::string name, float weight, float length, float width, float depth) : Deliverable(){
    this->name = name;
    this->weight = weight;
    this->length = length;
    this->width = width;
    this->depth = depth;
    this->orderType = "Parcel";
}

/**
 * A virtual override that calculates the size of the parcel
 * 
 * @return the size in cubic centimeters
 * 
*/
float Parcel::getSize() {
    return length*width*depth;
}

/**
 * A virtual override that calculates the price of the delivery based on size and weight
 * 
 * @return the price of the delivery
 * 
*/
float Parcel::getPrice() {
    float weightTerm = weight * PARCEL_PRICE_PER_KILO;
    float sizeTerm = getSize() * PARCEL_PRICE_PER_CUBIC_CM;
    return weightTerm + sizeTerm;
}