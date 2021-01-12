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
#include "algos.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/*

Acknowledgements:
Information from cplusplus.com and cppreference.com was used in the creation of
this program to handle string inputs and exceptions.

*/

vector<Customer *> allCustomers;

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
    cout    << endl
            << "1. Add a customer" << endl
            << "2. Delete a customer" << endl
            << "3. Add a delivery order" << endl
            << "4. Cancel a delivery order" << endl
            << "5. Record payment for a delivery order" << endl
            << "6. Get a printable shipping label for an order" << endl
            << "7. Deliver an order" << endl
            << "8. Print the status of orders for a customer" << endl
            << "9. Print a customer's orders to a file" << endl
            << "10. Load orders from shipping labels in a text file" << endl
            << "11. Sort pending orders by name" << endl
            << "12. Search for a pending order by name" << endl
            << "13. Quit" << endl
            << endl
            << "Non-delivery options: " << endl
            << "14. Get the sum of digits in a number" << endl
            << "15. Check a string for mirrordromes" << endl
            << endl;
}

/**
 * A comparator function used to test the sorting algorithms
 * found in algos.h
 * 
 * @param a - the first float to compare
 * @param b - the second float to compare
 * @return whether a < b
*/
bool compareFloats(float a, float b) {
    return a < b;
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

        try {
            switch (response) {
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
                // Print order statuses to a file
                printOrderStatusesToFile();
                break;
            case 10:
                // Read orders from file
                readOrders();
                break;
            case 11:
                // Sort orders
                sortOrders();
                break;
            case 12:
                // Search for an order
                searchForOrder();
                break;
            case 13:
                // Quit
                exit = true;
                break;
            case 14:
                // Sum digits
                sumDigits();
                break;
            case 15:
                // Count mirrordromes
                getMirrordromes();
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
            }
        }
        catch (const exception &e) {
            cout << e.what() << '\n';
        }

        if(!exit) {
            cout << endl;
            system("pause");
        }
    }

    return 0;
}