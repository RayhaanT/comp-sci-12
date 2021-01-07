#pragma once

#include <vector>

using namespace std;

template <class T>
void bubbleSort(vector<T, std::allocator<T>> *items, int count, bool (*compare)(T, T));