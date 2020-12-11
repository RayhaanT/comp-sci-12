#pragma once

#include <string>
#include <vector>
#include "deliverable.h"

class Customer {
public:

    // Constructor
    Customer(std::string name, std::string country, std::string region, std::string municipality, std::string address);
    Customer(std::string name, std::string addressString);

    // Get functions
    std::string getLocation();
    std::vector<std::string> getLocationArray();
    std::string getName();
    uint64_t getID();

    // Managing packages
    bool pay(int deliverableID);
    bool deliver(int deliverableID);

private:

    // Location data
    std::string name;
    std::string country;
    std::string region;
    std::string municipality;
    std::string address;

    // Package data
    std::vector<Deliverable> pendingOrders;
    std::vector<Deliverable> completedOrders;

    // Unique ID
    uint64_t id;
};