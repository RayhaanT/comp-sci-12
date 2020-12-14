#include "customer.h"
#include "main.h"
#include <stdexcept>

using namespace std;

uint64_t Customer::currentID = 0;

/**
 * The constructor for the Customer class. Takes in data about the customer's
 * name and location
 * 
 * @param _name - The customer's name
 * @param _country - The customer's country of residence
 * @param _region - The customer's region of residence (e.g. province)
 * @param _municipality - The customer's municipality of residence
 * @param _address - The customer's address, including unit or house number
 * 
*/
Customer::Customer(string _name, string _country, string _region, string _municipality, string _address) {
    this->name = _name;
    this->country = _country;
    this->region = _region;
    this->municipality = _municipality;
    this->address = _address;
    this->id = currentID;
    currentID++;
}

// This function was scrapped
// Customer::Customer(string _name, string addressString) {
//     this->name = _name;
//     vector<string> addressData;
//     string currentString = "";

//     for(int i = 0; i < address.size(); i++) {
//         if(addressString[i] == ',') {
//             addressData.push_back(stripString(currentString));
//         }
//         else {
//             currentString += addressString[i];
//         }
//     }
//     addressData.push_back(stripString(currentString));

//     if(addressData.size() < 4) {
//         throw runtime_error("Insufficient address data");
//     }

//     this->country = addressData[0];
//     this->region = addressData[1];
//     this->municipality = addressData[2];
//     this->address = addressData[3];
// }

/**
 * Compile the customer's location data into a label format
 * 
 * @return the customer's formatted location data
 * 
*/
string Customer::getLocation() {
    std::string fullAddress = name + "\n";
    fullAddress += address + "\n";
    fullAddress += municipality + ", " + region + ", " + country;
    return fullAddress;
}

/**
 * Gets the customer's name which is a private variable
 * 
 * @return the customer's name
 * 
*/
string Customer::getName() {
    return this->name;
}

/**
 * Gets the customer's ID which is a private variable
 * 
 * @return the customer's ID
 * 
*/
uint64_t Customer::getID() {
    return this->id;
}

/**
 * Marks a delivery assigned to the customer as paid
 * 
 * @return whether the process was successful
 * 
*/
bool Customer::pay(int deliverableID) {
    try {
        findDeliverable(deliverableID)->pay();
    }
    catch(const std::exception& e) {
        return false;
    }
    return true;
}

/**
 * Marks a delivery assigned to the customer as delivered
 * 
 * @return whether the process was successful
 * 
*/
bool Customer::deliver(int deliverableID) {
    try {
        Deliverable * d = findDeliverable(deliverableID);
        d->deliver();
        completedOrders.push_back(d);
        for (int i = 0; i < pendingOrders.size(); i++) {
            if(pendingOrders[i]->getID() == d->getID()) {
                pendingOrders.erase(pendingOrders.begin() + i);
                break;
            }
        }
        
    }
    catch(const std::exception& e) {
        return false;
    }
    return true;
}

/**
 * Finds a delivery order assigned to the customer based on the ID
 * 
 * @param deliverableID - The ID of the order being searched for
 * @return a pointer to the order
 * 
*/
Deliverable * Customer::findDeliverable(int deliverableID) {
    
    for(int i = 0; i < pendingOrders.size(); i++) {
        if(pendingOrders[i]->getID() == deliverableID) {
            return pendingOrders[i];
        }
    }
    for(int i = 0; i < completedOrders.size(); i++) {
        if(completedOrders[i]->getID() == deliverableID) {
            return completedOrders[i];
        }
    }
    throw runtime_error("Deliverable not found");
}