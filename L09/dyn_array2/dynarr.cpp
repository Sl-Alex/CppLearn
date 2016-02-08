#include "dynarr.h"
#include <algorithm>    // std::max

DynArr::DynArr()
{
    m_Arr = new int[DEFAULT_SIZE];
}

DynArr::~DynArr()
{
    delete[] m_Arr;
}

void DynArr::setSize(unsigned int val)
{
    m_Size = val;
    m_Capacity = val;
    resizeArr(val);
}

void DynArr::resizeArr(unsigned int NewSize)
{
    if (NewSize == m_Size) return;

    // Create a new array
    int * new_arr = new int [NewSize];

    // Copy all data
    for (unsigned int i = 0; i < std::min(NewSize,m_Size); ++i)
    {
        new_arr[i] = m_Arr[i];
    }

    // Change array size
    m_Size = NewSize;

    // Free old array
    delete[] m_Arr;

    // Update the pointer
    m_Arr = new_arr;
}

DynArr& DynArr::operator=(const DynArr& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
