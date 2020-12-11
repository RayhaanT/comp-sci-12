#include "deliverable.h"

uint64_t Deliverable::currentID = 0;

Deliverable::Deliverable() {
    this->id = currentID;
    currentID++;
}

bool Deliverable::pay() {
    this->paid = true;
}

bool Deliverable::deliver() {
    this->delivered = true;
}

uint64_t Deliverable::getID() {
    return this->id;
}

std::string Deliverable::getName() {
    return this->name;
}

bool Deliverable::isPaid() {
    return this->paid;
}

bool Deliverable::isDelivered() {
    return this->delivered;
}

float Deliverable::getWeight() {
    return this->weight;
}