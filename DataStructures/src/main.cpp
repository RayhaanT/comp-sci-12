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

bool compareFloats(float a, float b) {
    return a > b;
}


template <class T>
void bubbleSort(vector<T, std::allocator<T>> *list, bool (*compare)(T, T)) {
    T temp;

    for(int i = 1; i < list->size(); i++) {
        for(int x = list->size() - 1; x >= i; x--) {
            if (compare(list->operator[](x - 1), list->operator[](x))) {
                temp = list->operator[](x - 1);
                list->operator[](x - 1) = list->operator[](x);
                list->operator[](x) = temp;
            }
        }
    }
}

template <class T>
void insertionSort(vector<T, allocator<T>> *list, bool (*compare)(T, T)) {
    T temp;

    for(int i = 1; i < list->size(); i++) {
        int x = i - 1;
        temp = list->operator[](i);
        while (compare(list->operator[](x), temp) && x >= 0) {
            list->operator[](x + 1) = list->operator[](x);
            x--;
        }
        list->operator[](x + 1) = temp;
    }
}

template <class T>
bool genericMatch(T a, T b) {
    return a == b;
}

template <class T>
int linearSearch(vector<T, allocator<T>> list, T target, bool (*match)(T, T) = genericMatch) {
    for(int i = 0; i < list.size(); i++) {
        if(match(list[i], target)) {
            return i;
        }
    }

    return -1;
}

template <class T>
int binarySearch(vector<T, allocator<T>> list, T target, bool (*compare)(T, T), bool (*match)(T, T) = genericMatch) {
    int ceiling = list.size() - 1;
    int floor = 0;

    do {
        int currentIndex = floor + ((ceiling - floor) / 2);
        if(match(list[currentIndex], target)) {
            return currentIndex;
        }
        // If current value is greater than the target
        if(compare(list[currentIndex], target)) {
            ceiling = currentIndex - 1;
        }
        // If current value is less than the target
        else {
            floor = currentIndex + 1;
        }
    } while (ceiling >= floor);
    
    return -1;
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

    vector<float> f = {8, 2, 5, 7, 3, 6, 4, 1};
    insertionSort(&f, &compareFloats);
    for(float i : f) {
        cout << i << endl;
    }

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