# pragma once

#include <string>
#include "customer.h"
#include "deliverable.h"

// Utility functions
std::string stripString(std::string str);
std::string removeExcessDecimals(std::string str);
Customer * selectCustomer();
Deliverable * selectOrder(Customer * customer);

// Menu functions
void addCustomer();
void deleteCustomer();
void printOrderStatuses();
void printOrderStatusesToFile();
void addOrder();
void cancelOrder();
void recordPay();
void deliver();
void printLabel();
void readOrders();
void sortOrders();
void searchForOrder();
void sumDigits();
void getMirrordromes();

// Globals
extern std::vector<Customer *> allCustomers;
const Customer failedSearch("ERROR", "ERROR", "ERROR", "ERROR", "ERROR");