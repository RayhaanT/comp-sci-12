#include "truckdelivery.h"

/**
 * This is the constructor function for new truck delivery objects
 * 
 * @param name - The name of the order
 * @param weight - The weight of the object being delivered in kilograms
 *
*/
TruckDelivery::TruckDelivery(std::string name, float weight) : Deliverable() {
    this->name = name;
    this->weight = weight;
    this->orderType = "Truck Delivery";
}

/**
 * A virtual override to calculate the size for this delivery.
 * 
 * @return a number representing the size. Size is irrelevant for truck deliveries so it returns -1
 * 
*/
float TruckDelivery::getSize() {
    return -1;
}

/**
 * A virtual override to  calculate the price of the delivery based on weight.
 * 
 * @return the price of the delivery order
 * 
*/
float TruckDelivery::getPrice() {
    float extra = 0;
    if(weight > TRUCK_OVERSIZE_WEIGHT) {
        extra = (weight - TRUCK_OVERSIZE_WEIGHT) * TRUCK_PRICE_PER_KILO;
    }
    return extra + TRUCK_BASE_PRICE;
}