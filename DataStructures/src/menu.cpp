#include "main.h"
#include "customer.h"
#include "parcel.h"
#include "envelope.h"
#include "truckdelivery.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * Ask the user to select a Customer to manage. The system will search the allCustomers vector to find
 * one that matches the user's parameters of name and ID
 * 
 * @return a pointer to the selected Customer
 * 
*/
Customer * selectCustomer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Select a customer by name:" << endl;
    string name;
    getline(cin, name);

    vector<int> matchIndices;

    for(int i = 0; i < allCustomers.size(); i++) {
        if(allCustomers[i].getName() == name) {
            matchIndices.push_back(i);
        }
    }

    if(matchIndices.size() < 1) {
        cout << "There is no customer by that name" << endl;
        Customer f = failedSearch;
        return &f;
    }
    if(matchIndices.size() > 1) {
        while(1) {
            cout << "There are multiple customers by that name. Select the matching ID:" << endl;
            vector<int> ids;
            
            for (int i = 0; i < matchIndices.size(); i++) {
                int thisID = allCustomers[matchIndices[i]].getID();
                cout << i + 1 <<". " << thisID << endl;
            }
            
            int selection;
            cin >> selection;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(selection > 0) {
                return &allCustomers[matchIndices[selection - 1]];
            }
        }
    }
    else {
        return &allCustomers[matchIndices[0]];
    }
}

/**
 * Select an individual order from a customers list of pending orders
 * 
 * @param customer - The Customer from which to select the order
 * @return a pointer to the order selected
 * 
*/
Deliverable * selectOrder(Customer * customer) {
    cout << "Enter an order ID: ";
    int id;
    cin >> id;
    for(int i = 0; i < customer->pendingOrders.size(); i++) {
        if(customer->pendingOrders[i]->getID() == id) {
            return customer->pendingOrders[i];
        }
    }
    throw runtime_error("There is no order by that ID");
}

/**
 * Get input from the user and add a new Customer to the system.
*/
void addCustomer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "What's the customer's name? ";
    string name;
    getline(cin, name);

    string country, region, municipality, address;
    cout << "Country: " << endl;
    getline(cin, country);
    cout << "Region: " << endl;
    getline(cin, region);
    cout << "Municipality: " << endl;
    getline(cin, municipality);
    cout << "Address: " << endl;
    getline(cin, address);

    allCustomers.push_back(Customer(name, country, region, municipality, address));
    cout << "Successfully recorded" << endl;

    return;
}

/**
 * Delete a user-selected customer from the system
*/
void deleteCustomer() {
    Customer* selected = selectCustomer();
    int deleteIndex = 0;
    for(int i = 0; i < allCustomers.size(); i++) {
        if(allCustomers[i].getID() == selected->getID()) {
            deleteIndex = i;
        }
    }
    allCustomers.erase(allCustomers.begin() + deleteIndex);
}

/**
 * Print a cell of information for the status table.
 * 
 * @param data - The string that should go in the cell
 * @param length - The total length of the cell so the proper amount of whitespace can be filled in
 * 
*/
void printCell(string data, int length) {
    cout << "| ";
    cout << data;
    int numberOfSpaces = length - data.size();
    for(int i = 0; i < numberOfSpaces; i++) {
        cout << " ";
    }
    cout << " ";
}

/**
 * Print a table of all orders, completed and pending, from a customer
*/
void printOrderStatuses() {
    Customer* selected = selectCustomer();

    cout << endl << "Pending orders:" << endl;
    cout << "| Name                    |      Type      | Paid? |   Size   |  Price  |  Weight  | ID        |" << endl;
    for (Deliverable * d : selected->pendingOrders) {
        string paid = d->isPaid() ? "Yes" : "No";
        string size = removeExcessDecimals(to_string(d->getSize()));
        if(d->getSize() == -1) {
            size = "Special";
        }

        printCell(d->getName(), 23);
        printCell(d->orderType, 14);
        printCell(paid, 5);
        printCell(size, 8);
        printCell("$" + removeExcessDecimals(to_string(d->getPrice())), 7);
        printCell(removeExcessDecimals(to_string(d->getWeight())) + " kg", 8);
        printCell(to_string(d->getID()), 9);
        cout << "|" << endl;
    }

    cout << endl << "Completed orders:" << endl;
    cout << "| Name                    |      Type      |   Size   |  Price  |  Weight  | ID        |" << endl;
    for (Deliverable * d : selected->completedOrders) {
        string paid = d->isPaid() ? "Yes" : "No";
        string delivered = d->isDelivered() ? "Yes" : "No";
        string size = removeExcessDecimals(to_string(d->getSize()));
        if (d->getSize() == -1) {
            size = "Special";
        }

        printCell(d->getName(), 23);
        printCell(d->orderType, 14);
        printCell(size, 8);
        printCell("$" + removeExcessDecimals(to_string(d->getPrice())), 7);
        printCell(removeExcessDecimals(to_string(d->getWeight())) + " kg", 8);
        printCell(to_string(d->getID()), 9);
        cout << "|" << endl;
    }
}

/**
 * Add a new delivery order to a customer's account
*/
void addOrder() {
    Customer* customer = selectCustomer();

    string name;
    cout << "What should the order be called?" << endl;
    getline(cin, name);

    float weight;
    cout << "How heavy are the items being delivered? (kg)" << endl;
    cin >> weight;

    float length;
    cout << "Enter the length of the items to determine the necessary packaging: (cm)" << endl;
    cin >> length;
    float width;
    cout << "Enter the width of the items: (cm)" << endl;
    cin >> width;
    float depth;
    cout << "Enter the depth of the items: (cm)" << endl;
    cin >> depth;

    if(width < 30 && length < 30 && depth < 2) {
        customer->pendingOrders.push_back(new Envelope(name, weight, length, width));
        cout << "The order was successfully added. It will be delivered in an envelope." << endl;
    }
    else if(width < 100 && length < 100 && depth < 100 && weight < 100) {
        customer->pendingOrders.push_back(new Parcel(name, weight, length, width, depth));
        cout << "The order was successfully added. It will be delivered in a parcel." << endl;
    }
    else {
        customer->pendingOrders.push_back(new TruckDelivery(name, weight));
        cout << "The order was successfully added. It will be delivered specially in a truck." << endl;
    }
}

/**
 * Remove a delivery order from a customer's account
*/
void cancelOrder() {
    Customer *customer = selectCustomer();
    try {
        Deliverable *order = selectOrder(customer);
        for (int i = 0; i < customer->pendingOrders.size(); i++) {
            if(customer->pendingOrders[i]->getID() == order->getID()) {
                customer->pendingOrders.erase(customer->pendingOrders.begin() + i);
            }
        }
    }
    catch(const exception &e) {
        cout << e.what();
    }
}

/**
 * Record payment on an order
*/
void recordPay() {
    Customer *customer = selectCustomer();
    Deliverable *order;
    try {
        order = selectOrder(customer);
    }
    catch(const exception &e) {
        cout << e.what();
        return;
    }

    float payment;
    cout << "How much payment was recieved? ($)" << endl;
    cin >> payment;
    if(payment >= order->getPrice()) {
        if(customer->pay(order->getID())) {
            cout << "Payment succesfully recorded." << endl;
            cout << "$" << removeExcessDecimals(to_string(payment-order->getPrice())) << " should be refunded to the customer." << endl;
            return;
        }
        cout << "An error occurred with locating the order in the system." << endl;
        return;
    }
    cout << "The payment was insufficient for this order." << endl;
}


/**
 * Record an order as delivered if it has been paid
*/
void deliver() {
    Customer *customer = selectCustomer();
    Deliverable *order;
    try {
        order = selectOrder(customer);
    }
    catch (const exception &e) {
        cout << e.what();
        return;
    }

    if(!order->isPaid()) {
        cout << "This order has not been paid for. It cannot be delivered." << endl;
    }
    else {
        if(customer->deliver(order->getID())) {
            cout << "Order succesfully delivered." << endl;
        }
        else {
            cout << "An error occurred with locating the order in the system." << endl;
        }
    }
}

/**
 * Write the shipping label for an order to a text file.
 * This includes the customer's address data, the type of delivery, and price
*/
void printLabel() {
    Customer *customer = selectCustomer();
    Deliverable *order;
    try {
        order = selectOrder(customer);
    }
    catch (const exception &e) {
        cout << e.what();
        return;
    }

    cout << "What should the file be called (do not include the file extension)" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string fileName;
    getline(cin, fileName);

    ofstream label;
    label.open(fileName + ".txt");
    label << customer->getLocation();
    label << "\n\n" + order->orderType + "\n";
    label << "$" + to_string(order->getPrice()) + "\n";
    label.close();
    return;
}

/**
 * Read order data from a specially formatted file and add the order to a customer's account
*/
void readOrder() {
    Customer *customer = selectCustomer();

    std::cout << 
    "The label format can be found in orderFormat.txt.\n"
    "Input the name of the text file to be read (do not include the .txt file extension)." << endl;
    string fileName;
    getline(cin, fileName);

    string line;
    ifstream orderFile(fileName + ".txt");
    if (orderFile.is_open())
    {
        int count = 0;
        string name;
        float length, width, depth, weight;
        while (getline(orderFile, line))
        {
            switch (count) {
                case 0:
                    name = line;
                    break;
                case 1:
                    weight = stof(line);
                    break;
                case 2:
                    length = stof(line);
                    break;
                case 3:
                    width = stof(line);
                    break;
                case 4:
                    depth = stof(line);
                    break;
            }
            count++;
            if(count > 4) {
                break;
            }
        }

        if (width < 30 && length < 30 && depth < 2) {
            customer->pendingOrders.push_back(new Envelope(name, weight, length, width));
            cout << "The order was successfully added. It will be delivered in an envelope." << endl;
        }
        else if (width < 100 && length < 100 && depth < 100 && weight < 100) {
            customer->pendingOrders.push_back(new Parcel(name, weight, length, width, depth));
            cout << "The order was successfully added. It will be delivered in a parcel." << endl;
        }
        else {
            customer->pendingOrders.push_back(new TruckDelivery(name, weight));
            cout << "The order was successfully added. It will be delivered specially in a truck." << endl;
        }

        orderFile.close();
    }

    else {
        cout << "Unable to open file";
    }

    return;
}