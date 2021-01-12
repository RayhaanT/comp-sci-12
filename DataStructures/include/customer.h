#pragma once

#include <string>
#include <vector>
#include "deliverable.h"

/**
 * This class handles customer accounts. It tracks all orders related
 * to the customer as well as their location/address data.
*/
class Customer {
public:

    // Constructor
    Customer(std::string _name, std::string _country, std::string _region, std::string _municipality, std::string _address);
    // Customer(std::string _name, std::string addressString); //Scrapped

    // Get functions
    std::string getLocation();
    std::string getName();
    uint64_t getID();

    // Managing packages
    bool pay(int deliverableID);
    bool deliver(int deliverableID);

    // Package data (pointers so the actual data goes on the heap)
    std::vector<Deliverable*> pendingOrders;
    std::vector<Deliverable*> completedOrders;

private:

    // Functions
    Deliverable * findDeliverable(int deliverableID);

    // Location data
    std::string name;
    std::string country;
    std::string region;
    std::string municipality;
    std::string address;

    // Unique ID
    uint64_t id;
    static uint64_t currentID;
};