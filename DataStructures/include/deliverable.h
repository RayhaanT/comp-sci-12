#pragma once

#include <string>

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
    virtual float getSize() {};
    virtual float getPrice() {};

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