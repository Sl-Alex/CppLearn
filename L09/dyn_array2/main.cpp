#include <iostream>
#include "dynarr.h"

using namespace std;

int * alloc_more(int * arr, int &arr_size, const unsigned int increment)
{
    // Create a new array
    int * new_arr = new int [arr_size + increment];

    // Copy all data
    for (int i = 0; i < arr_size; i++)
    {
        new_arr[i] = arr[i];
    }

    // Increase array size
    arr_size += increment;

    // Free old memory
    delete[] arr;

    return new_arr;
}

int main()
{
    DynArr arr;

    cout << "Enter any numbers, one by one." << endl;
    cout << "They will be added to the array." << endl;
    cout << "Zero means the end of the input." << endl;
    cout << "Array size will be adjusted automatically" << endl;

    int tmp;
    cin >> tmp;

    while (tmp)
    {
        arr[arr.getSize()] = tmp;
        cin >> tmp;
    }

    cout << "==================" << endl;

    cout << "Result of the input:" << endl;
    cout << arr << endl;

    cout << "Array after copy in the constructor:" << endl;
    DynArr arr2 = arr;
    cout << arr2 << endl;

    cout << "Array after the assignment:" << endl;
    DynArr arr3 = arr;
    cout << arr3 << endl;

    return 0;
}
