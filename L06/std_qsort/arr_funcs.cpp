#include <iostream>

using namespace std;

int * arr_alloc_more(int * arr, int * arr_size, const unsigned int increment)
{
    // Create a new array
    int * new_arr = new int [*arr_size + increment];

    // Copy all data
    for (int i = 0; i < *arr_size; i++)
    {
        new_arr[i] = arr[i];
    }

    // Increase array size
    *arr_size += increment;

    // Free old memory
    delete[] arr;

    return new_arr;
}

void arr_print(int * arr, int data_cnt)
{
    for (int i = data_cnt - 1; i >= 0; --i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
