#include "sort.h"

using namespace std;

template <class T>
void bubbleSort(vector<T, std::allocator<T>> *items, int count, bool (*compare)(T, T))
{
    T t;

    for (int a = 1; a < count; a++)
        for (int b = count - 1; b >= a; b--)
            if (compare(items[b - 1], items[b]))
            {
                t = items[b - 1];
                items[b - 1] = items[b];
                items[b] = t;
            }
}