/**
 * The main file
 * 
 * @author Rayhaan Tanweer
 * @since 6-Jan-2020
 * @version 1.0
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

/**
 * Generates a random value from 0 to the maximum, exclusive
 * 
 * @param max - the maximum value of the random range
 * @param decimals - the number of decimal places to calculate
 * @return the random floating point value
*/
float random(int max, int decimals = 0) {
    if(decimals) {
        return (float)(rand() % (int)(max * pow(10, decimals))) / pow(10, decimals);
    } 
    return rand() % max;
}

/**
 * The main function. This is the first method that gets called
 * when the executable is run
 * 
 * @return a number representing the exit status
*/
int main() {

    string fileName;
    cout << "Filename:" << endl;
    getline(cin, fileName);

    double entries;
    cout << "Entries:" << endl;
    cin >> entries;

    ofstream dump;
    dump.open(fileName + ".txt");

    for(int i = 0; i < entries; i++) {
        string name = "";
        float weight, length, width, depth;

        int nameLength = random(21) + 5;
        for (int i = 0; i < nameLength; i++) {
            name += random(26) + 'a';
        }
        
        int type = random(3);
        switch (type)
        {
        case 0: // Envelope
            weight = random(100, 2);
            length = random(30, 2);
            width = random(30, 2);
            depth = random(2, 2);
            break;
        case 1: // Parcel
            weight = random(100, 2);
            length = random(100, 2);
            width = random(100, 2);
            depth = random(100, 2);
            break;
        case 2: // Truck
            weight = random(2000, 2);
            length = random(1000, 2);
            width = random(200, 2);
            depth = random(200, 2);
            break;
        }

        dump << name << "\n";
        dump << weight << "\n";
        dump << length << "\n";
        dump << width << "\n";
        dump << depth << "\n";
        dump << "\n";
    }

    dump.close();
    return 0;
}