/**
 * The main file
 * 
 * @author Rayhaan Tanweer
 * @since 6-Dec-2020
 * @version 1.0
 */

#include "main.h"
#include "customer.h"
#include "parcel.h"
#include "envelope.h"
#include "truckdelivery.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/*

Acknowledgements:
Information from cplusplus.com and cppreference.com was used in the creation of
this program to handle string inputs and exceptions.

*/

vector<Customer> allCustomers;
Customer failedSearch("ERROR", "ERROR", "ERROR", "ERROR", "ERROR");

string stripString(string str) {
    if(str.empty()) {
        return "";
    }
    while(isspace(str[0])) {
        str.erase(str.begin());
        if(str.empty()) {
            return "";
        }
    }
    while(isspace(str[str.size()-1])) {
        str.erase(str.end());
        if(str.empty()) {
            return "";
        }
    }
    return str;
}

string removeExcessDecimals(string str) {
    for (int i = 0; i < str.size(); i++)
    {
        if(str[i] == '.') {
            if(str.size() - i > 3) {
                str.erase(str.begin() + i + 3, str.end());
            }
            return str;
        }
    }
    return str;
}

void printMenu() {
    cout << endl;
    cout << "1. Add a customer" << endl;
    cout << "2. Delete a customer" << endl;
    cout << "3. Add a delivery order" << endl;
    cout << "4. Cancel a delivery order" << endl;
    cout << "5. Record payment for a delivery order" << endl;
    cout << "6. Get a printable shipping label for an order" << endl;
    cout << "7. Deliver an order" << endl;
    cout << "8. Print the status of orders for a customer" << endl;
    cout << "9. Load orders from shipping labels in a text file" << endl;
    cout << "10. Quit" << endl;
    cout << endl;
}

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
        return &failedSearch;
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

void printCell(string data, int length) {
    cout << "| ";
    cout << data;
    int numberOfSpaces = length - data.size();
    for(int i = 0; i < numberOfSpaces; i++) {
        cout << " ";
    }
    cout << " ";
}

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
    if(payment > order->getPrice()) {
        if(customer->pay(order->getID())) {
            cout << "Payment succesfully recorded." << endl;
            return;
        }
        cout << "An error occurred with locating the order in the system." << endl;
        return;
    }
    cout << "The payment was insufficient for this order." << endl;
}

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

int main() {

    cout <<
    "Welcome to the package management system.\n"
    "Here you can track and manage delivery orders\n"
    "for all your different customers." << endl;

    bool exit = false;

    while(!exit) {
        printMenu();
        string strResponse;
        cin >> strResponse;
        int response = 0;
        try {
            response = stoi(strResponse);
        }
        catch(const exception& e) {
            cout << e.what() << '\n';
        }
        
        if(!response) {
            response = -1;
        }

        switch (response)
        {
        case 1:
            // Add customer
            addCustomer();
            break;
        case 2:
            // Delete customer
            deleteCustomer();
            break;
        case 3:
            // Add order
            addOrder();
            break;
        case 4:
            // Cancel order
            cancelOrder();
            break;
        case 5:
            // Record payment
            recordPay();
            break;
        case 6:
            // Write label to file
            printLabel();
            break;
        case 7:
            // Mark an order as delivered
            deliver();
            break;
        case 8:
            // Print order statuses
            printOrderStatuses();
            break;
        case 9:
            // Read orders from file
            readOrder();
            break;
        case 10:
            // Quit
            exit = true;
            break;

        default:
            cout << "Invalid choice." << endl;
            break;
        }
        cout << endl;
    }

    return 0;
}