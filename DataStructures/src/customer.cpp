#include "customer.h"
#include "main.h"

using namespace std;

uint64_t Customer::currentID = 0;

Customer::Customer(string _name, string _country, string _region, string _municipality, string _address) {
    this->name = _name;
    this->country = _country;
    this->region = _region;
    this->municipality = _municipality;
    this->address = _address;
    this->id = currentID;
    currentID++;
}

Customer::Customer(string _name, string addressString) {
    this->name = _name;
    vector<string> addressData;
    string currentString = "";

    for(int i = 0; i < address.size(); i++) {
        if(addressString[i] == ',') {
            addressData.push_back(stripString(currentString));
        }
        else {
            currentString += addressString[i];
        }
    }
    addressData.push_back(stripString(currentString));

    if(addressData.size() < 4) {
        throw "Insufficient address data";
    }

    this->country = addressData[0];
    this->region = addressData[1];
    this->municipality = addressData[2];
    this->address = addressData[3];
}

string Customer::getLocation() {
    
}

vector<string> Customer::getLocationArray() {
    
}

string Customer::getName() {
    return this->name;
}

uint64_t Customer::getID() {
    return this->id;
}

bool Customer::pay(int deliverableID) {
    try {
        findDeliverable(deliverableID)->pay();
    }
    catch(const std::exception& e) {
        return false;
    }
    return true;
}

bool Customer::deliver(int deliverableID) {
    try {
        findDeliverable(deliverableID)->deliver();
    }
    catch(const std::exception& e) {
        return false;
    }
    return true;
}

Deliverable * Customer::findDeliverable(int deliverableID) {
    for (Deliverable d : pendingOrders) {
        if(d.getID() == deliverableID) {
            return &d;
        }
    }
    for (Deliverable d : completedOrders) {
        if(d.getID() == deliverableID) {
            return &d;
        }
    }
    throw "Deliverable not found";
}