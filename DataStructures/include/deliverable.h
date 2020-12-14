#pragma once

#include <string>

/**
 * This class is a parent class for the other types of delivery
 * orders (envelopes, parcels, and special truck deliveries).
 * It has properties for delivery data and status, and virtual
 * functions that are overridden by the child classes
 * to do unique price and size calculations.
*/
class Deliverable {
public:

    Deliverable();

    // Order status updates
    bool pay();
    bool deliver();

    // Get Functions
    uint64_t getID();
    std::string getName();
    bool isPaid();
    bool isDelivered();
    float getWeight();

    // Virtual functions
    virtual float getSize() {return 0;};
    virtual float getPrice() {return 0;};

    // Type of order name
    std::string orderType;

protected:

    // Package information
    float weight;
    std::string name;

private:

    // Order status
    bool paid = false;
    bool delivered = false;

    // ID
    uint64_t id;
    static uint64_t currentID;
};