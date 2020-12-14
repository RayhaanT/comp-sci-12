#include "truckdelivery.h"

TruckDelivery::TruckDelivery(std::string name, float weight) : Deliverable() {
    this->name = name;
    this->weight = weight;
    this->orderType = "Truck Delivery";
}

float TruckDelivery::getSize() {
    return -1;
}

float TruckDelivery::getPrice() {
    float extra = 0;
    if(weight > TRUCK_OVERSIZE_WEIGHT) {
        extra = (weight - TRUCK_OVERSIZE_WEIGHT) * TRUCK_PRICE_PER_KILO;
    }
    return extra + TRUCK_BASE_PRICE;
}