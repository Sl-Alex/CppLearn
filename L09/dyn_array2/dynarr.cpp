#include "dynarr.h"
#include <iostream>
#include <algorithm>    // std::max

using namespace std;

/// @brief Default constructor
DynArr::DynArr()
{
    m_Arr = new int[DEFAULT_SIZE];
    m_Size = 0;
    m_Capacity = DEFAULT_SIZE;
}

/// @brief Assignment from constructor
DynArr::DynArr(const DynArr & from)
{
    m_Capacity = from.getCapacity();
    m_Size = from.getSize();

    m_Arr = new int[m_Capacity];

    for (unsigned int i = 0; i < m_Size; ++i)
    {
        m_Arr[i] = from.m_Arr[i];
    }
}

/// Default destructor
DynArr::~DynArr()
{
    delete[] m_Arr;
}

void DynArr::setSize(unsigned int val)
{
    if (m_Size > m_Capacity)
        reallocArr(val);

    m_Size = val;
}

void DynArr::setCapacity(unsigned int val)
{
    reallocArr(val);
    if (m_Size > m_Capacity)
        m_Size = m_Capacity;
}

void DynArr::reallocArr(unsigned int NewCapacity)
{
    if (NewCapacity == m_Capacity) return;

#ifdef DEBUG
    cout << "Realloc to " << NewCapacity << " elements" << endl;
#endif

    // Create a new array
    int * new_arr = new int [NewCapacity];

    // Copy all relevant data
    for (unsigned int i = 0; i < std::min(NewCapacity,m_Size); ++i)
    {
        new_arr[i] = m_Arr[i];
    }

    // Update array capacity
    m_Capacity = NewCapacity;

    // Free old array
    delete[] m_Arr;

    // Update the pointer
    m_Arr = new_arr;
}

DynArr& DynArr::operator=(const DynArr& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

#ifdef DEBUG
    cout << "Assignment start" << endl;
#endif // DEBUG

    // Relocate our array in order to have the same capacity
    reallocArr(rhs.getCapacity());

    // Update our size
    m_Size = rhs.getSize();

    // Copy all relevant data
    for (unsigned int i = 0; i < m_Size; ++i)
    {
        m_Arr[i] = rhs.m_Arr[i];
    }

    // Return ourselves
    return *this;
}

int& DynArr::operator[](unsigned int idx)
{
    // Check the actual capacity
    if (idx >= m_Capacity)
    {
        reallocArr(m_Capacity + SIZE_INCREMENT);
    }
    if (idx >= m_Size)
    {
        m_Size = idx + 1;
#ifdef DEBUG
        cout << "Actual size changed to " << m_Size << " elements" << endl;
#endif // DEBUG
    }

    return m_Arr[idx];
}

int DynArr::operator[](unsigned int idx) const
{
    if (idx < m_Size)
        return m_Arr[idx];

    return 0;
}

ostream& operator<<(ostream& os, const DynArr& a)
{
    if (a.getSize() == 0) return os;

    for (unsigned int i = 0; i < a.getSize() - 1; ++i)
        os << a[i] << ' ';

    if (a.getSize() > 0)
    os << a[a.getSize() - 1];

    return os;
}
