#ifndef DYNARR_H
#define DYNARR_H

#include <iostream>
using namespace std;

class DynArr
{
    public:
        static const unsigned int DEFAULT_SIZE = 5;
        static const unsigned int SIZE_INCREMENT = 5;

        DynArr();
        DynArr(const DynArr &from);
        ~DynArr();

        DynArr& operator=(const DynArr& rhs);
        int& operator[](unsigned int idx);
        int operator[](unsigned int idx) const;

        unsigned int getSize() const { return m_Size; }
        void setSize(unsigned int val);

        unsigned int getCapacity() const { return m_Capacity; }
        void setCapacity(unsigned int val);

    protected:
    private:
        int * m_Arr;
        void reallocArr(unsigned int NewCapacity);
        unsigned int m_Size; //!< Member variable "m_Size"
        unsigned int m_Capacity; //!< Member variable "m_Capacity"
};


ostream& operator<<(ostream& os, const DynArr & a);

#endif // DYNARR_H
