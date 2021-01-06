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

/**
 * Strips whitespace from the beginning and ends of strings
 * 
 * @param str - The string to be stripped
 * @return the stripped string
 *
*/
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

/**
 * Take a string that represents a floating point value and reduce it to only show 2 decimal places
 * 
 * @param str - The string that should be compressed
 * @return the rounded string
 * 
*/
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

/**
 * Print the main menu of the application to the console
*/
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

/**
 * The main function. This is the first thing that gets called when the executable is run.
 * 
 * @return an integer value representing the exit status
*/
int main() {

    cout <<
    "Welcome to the package management system.\n"
    "Here you can track and manage delivery orders\n"
    "for all your different customers.\n" << endl;

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