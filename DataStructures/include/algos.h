/**
 * This file contains function definitions because of how C++ handles templates.
 * If I define the functions in their own source file, I also need to declare a
 * variation of each using each different datatype (float, int, string, Customer, etc.).
 * Those declarations are not needed when the functions are defined in the header.
*/

#pragma once

#include <vector>
#include <iostream>

using namespace std;

// Recursion
int iterativeSum(int num);
int recursiveSum(int num);
int iterativePalindromes(string str);
int recursivePalindromes(string str);
int iterativeMirrordromes(string str);
int recursiveMirrordromes(string str);

/**
 * A generic function that takes a list of some kind and a comparator function
 * and sorts it using the bubble sort algorithm. As it uses pointers, returning
 * the list is not necessary.
 * 
 * @param list - A pointer to the vector to be sorted
 * @param compare - A pointer to the function used to compare objects
 *
*/
template <class T>
void bubbleSort(vector<T, std::allocator<T>> *list, bool (*compare)(T, T)) {
    T temp;

    for(int i = 1; i < list->size(); i++) {
        for(int x = list->size() - 1; x >= i; x--) {
            if(compare(list->at(x), list->at(x - 1))) {
                temp = list->at(x - 1);
                list->at(x - 1) = list->at(x);
                list->at(x) = temp;
            }
        }
    }
}

/**
 * A generic function that takes a list of some kind and a comparator function
 * and sorts it using the insertion sort algorithm
 * 
 * @param list - A pointer to the vector to be sorted
 * @param compare - A pointer to the function used to compare objects
 *
*/
template <class T>
void insertionSort(vector<T, allocator<T>> *list, bool (*compare)(T, T)) {
    T temp;

    for(int i = 1; i < list->size(); i++) {
        int x = i - 1;
        temp = list->at(i);
        while (x >= 0 && compare(temp, list->at(x))) {
            list->at(x + 1) = list->at(x);
            x--;
        }
        list->at(x + 1) = temp;
    }
}

/**
 * A generic function that acts as the default comparator for searches
 * 
 * @param a - The first value to compare
 * @param b - The second value to compare
 * @return true if a and b are equal, false otherwise
 *
*/
template <class T>
bool genericMatch(T a, T b) {
    return a == b;
}

/**
 * A generic function that searches for a given value in a list using linear
 * search. There is also the option to include a custom comparator for
 * custom datatypes
 * 
 * @param list - The vector to be searched
 * @param target - The value to be searched for
 * @param match - A function pointer for a custom comparator. Optional.
 * @return the index of the target value in the list, -1 if not found
 *
*/
template <class T>
int linearSearch(vector<T, allocator<T>> list, T target, bool (*match)(T, T) = genericMatch) {
    for(int i = 0; i < list.size(); i++) {
        if(match(list[i], target)) {
            return i;
        }
    }

    return -1;
}

/**
 * A generic function that searches for a given value in a list using binary
 * search. There is also the option to include a custom comparator for
 * custom datatypes
 * 
 * @param list - The vector to be searched
 * @param target - The value to be searched for
 * @param compare - A function pointer used to compare objects
 * @param match - A function pointer for a custom comparator. Optional.
 * @return the index of the target value in the list, -1 if not found
 *
*/
template <class T>
int binarySearch(vector<T, allocator<T>> list, T target, bool (*compare)(T, T), bool (*match)(T, T) = genericMatch) {
    int ceiling = list.size() - 1;
    int floor = 0;

    do {
        int currentIndex = floor + ((ceiling - floor) / 2);
        if(match(target, list[currentIndex])) {
            return currentIndex;
        }
        // If current value is greater than the target
        if(compare(target, list[currentIndex])) {
            ceiling = currentIndex - 1;
        }
        // If current value is less than the target
        else {
            floor = currentIndex + 1;
        }
    } while (ceiling >= floor);
    
    return -1;
}