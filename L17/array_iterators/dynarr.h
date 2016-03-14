#ifndef DYNARR_H
#define DYNARR_H

#include <iostream>
using namespace std;

// iterator class is parametrized by pointer type
template <typename T>
class DynArrIterator : public std::iterator<std::forward_iterator_tag, T>
{
    T* p;
public:
    DynArrIterator() :p(0) {}   // Default constructor, initialize pointer;
    explicit DynArrIterator(T* x) :p(x) {}  // Constructor from the existing pointer
    //! Надмірна --- буде створено автоматично, наведено для повноти
    DynArrIterator(const DynArrIterator& mit) : p(mit.p) {} // Copy constructor (is implemented by default)
    DynArrIterator& operator++() {  // Prefix Increment operator
        ++p;
        return *this;
    }
    DynArrIterator operator++(int) // Postfix increment operator
    {
            DynArrIterator tmp(*this);
            operator++();
            return tmp;
    }
    bool operator==(const DynArrIterator& rhs) const {
        return p==rhs.p;
    }
    bool operator!=(const DynArrIterator& rhs) const {
        return p!=rhs.p;
    }
    int& operator*() const {
        return *p;
    }
};

template <typename T>
class DynArr
{
    public:
        DynArrIterator<T> begin() {return DynArrIterator<T>(m_Arr);}
        DynArrIterator<T> end() {return DynArrIterator<T>(&m_Arr[m_Size]);}
        static const size_t DEFAULT_SIZE = 5;
        static const size_t SIZE_INCREMENT = 5;

        DynArr()
        {
            m_Arr = new T[DEFAULT_SIZE];
            m_Size = 0;
            m_Capacity = DEFAULT_SIZE;
        }
        DynArr(const DynArr & from)
        {
            m_Capacity = from.getCapacity();
            m_Size = from.getSize();

            m_Arr = new T[m_Capacity];

            for (size_t i = 0; i < m_Size; ++i)
            {
                m_Arr[i] = from.m_Arr[i];
            }
        }
        ~DynArr()
        {
            delete[] m_Arr;
        }

        T& operator=(const DynArr& rhs)
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
            for (size_t i = 0; i < m_Size; ++i)
            {
                m_Arr[i] = rhs.m_Arr[i];
            }

            // Return ourselves
            return *this;
        }
        T& operator[](size_t idx)
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
        T operator[](size_t idx) const
        {
            if (idx < m_Size)
                return m_Arr[idx];

            return T();
        }

        size_t getSize() const { return m_Size; }
        void setSize(size_t val)
        {
            if (m_Size > m_Capacity)
                reallocArr(val);

            m_Size = val;
        }

        size_t getCapacity() const { return m_Capacity; }
        void setCapacity(size_t val)
        {
            reallocArr(val);
            if (m_Size > m_Capacity)
                m_Size = m_Capacity;
        }

        friend ostream& operator<<(ostream& os, const DynArr & a)
        {
            if (a.getSize() == 0) return os;

            for (size_t i = 0; i < a.getSize() - 1; ++i)
                os << a[i] << '_';

            if (a.getSize() > 0)
            os << a[a.getSize() - 1];

            return os;
        }
    protected:
    private:
        T * m_Arr;
        void reallocArr(size_t NewCapacity)
        {
            if (NewCapacity == m_Capacity) return;

        #ifdef DEBUG
            cout << "Realloc to " << NewCapacity << " elements" << endl;
        #endif

            // Create a new array
            T * new_arr = new T [NewCapacity];

            // Copy all relevant data
            for (size_t i = 0; i < std::min(NewCapacity,m_Size); ++i)
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
        size_t m_Size; //!< Member variable "m_Size"
        size_t m_Capacity; //!< Member variable "m_Capacity"
};

#endif // DYNARR_H
