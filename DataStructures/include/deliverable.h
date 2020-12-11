#pragma once

#include <string>

class Deliverable {
public:

    // Order status updates
    bool pay();
    bool deliver();

    // Get Functions
    uint64_t getID();
    std::string getName();
    bool getPaid();
    bool getDelivered();

private:

    // Order status
    bool paid = false;
    bool delivered = false;

    // Package information
    float weight;
    std::string name;

    // ID
    uint64_t id;
};