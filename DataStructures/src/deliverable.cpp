#include "deliverable.h"

uint64_t Deliverable::currentID = 0;

/**
 * The constructor for the Deliverable class that assigns a unique ID to each instance
*/
Deliverable::Deliverable() {
    this->id = currentID;
    currentID++;
}

/**
 * Marks the order as paid
 * 
 * @return if the object is paid
 * 
*/
bool Deliverable::pay() {
    this->paid = true;
    return paid;
}

/**
 * Marks the order as delivered
 * 
 * @return if the object is delivered
 * 
*/
bool Deliverable::deliver() {
    this->delivered = true;
    return delivered;
}

/**
 * Gets the order ID which is a private variable
 * 
 * @return the order ID
 * 
*/
uint64_t Deliverable::getID() {
    return this->id;
}

/**
 * Gets the order name which is a private variable
 * 
 * @return the order name
 * 
*/
std::string Deliverable::getName() {
    return this->name;
}

/**
 * Gets whether the order has been paid for
 * 
 * @return a boolean representing whether the order has been paid for
 * 
*/
bool Deliverable::isPaid() {
    return this->paid;
}

/**
 * Gets whether the order has been delivered
 * 
 * @return a boolean representing whether the order has been delivered
 * 
*/
bool Deliverable::isDelivered() {
    return this->delivered;
}

/**
 * Gets the order weight which is a private variable
 * 
 * @return the order weight in kilograms
 * 
*/
float Deliverable::getWeight() {
    return this->weight;
}