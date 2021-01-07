#pragma once

#include <vector>

using namespace std;

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