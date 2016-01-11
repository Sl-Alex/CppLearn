#include <iostream>

using namespace std;

/// @brief Array size, should be even
const int ARR_SIZE = 8;
/// @brief Array itself
int arr[ARR_SIZE];

void arr_swap(int * a, int * b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

void printarr(void)
{
    for (int i = 0; i < ARR_SIZE; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    cout << "Enter " << ARR_SIZE << " numbers separated by space and press Enter" << endl;

    // Input all numbers
    for (int i = 0; i < ARR_SIZE; ++i)
    {
        cin >> arr[i];
    }

    cout << "Initial state of the array" << endl;
    printarr();

    // Swap each two consecutive numbers
    for (int i = 0; i < ARR_SIZE / 2; ++i)
    {
        arr_swap(&arr[i*2], &arr[i*2+1]);
    }

    cout << "Numbers are swapped" << endl;
    printarr();

    // Reverse order
    for (int i = 0; i < ARR_SIZE / 2; ++i)
    {
        arr_swap(&arr[ARR_SIZE - i - 1], &arr[i]);
    }

    cout << "Array is reversed" << endl;
    printarr();

    cout << "====================" << endl;
    // Bubble sort
    for (int i = 0; i < ARR_SIZE - 1; ++i)
    {
        for (int j = 0; j < ARR_SIZE - i; ++j)
        {
            if (arr[j-1] > arr[j])
            {
                cout << "Swapping #" << j << " and #" << j+1 << endl;
                arr_swap(&arr[j-1], &arr[j]);
                printarr();
            }
        }
    }

    cout << "Array is sorted (bubble sort)" << endl;
    printarr();

    return 0;
}
