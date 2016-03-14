#ifndef FIXARR_H
#define FIXARR_H

#include <iostream>
using namespace std;

template <typename T>
class FixArrIterator : public std::iterator<std::forward_iterator_tag, T>
{
    T* p;
public:
    FixArrIterator() :p(0) {}   // Default constructor, initialize pointer;
    explicit FixArrIterator(T* x) :p(x) {}  // Constructor from the existing pointer
    //! ������� --- ���� �������� �����������, �������� ��� �������
    FixArrIterator(const FixArrIterator& mit) : p(mit.p) {} // Copy constructor (is implemented by default)
    FixArrIterator& operator++() {  // Prefix Increment operator
        ++p;
        return *this;
    }
    FixArrIterator operator++(int) // Postfix increment operator
    {
            FixArrIterator tmp(*this);
            operator++();
            return tmp;
    }
    bool operator==(const FixArrIterator& rhs) const {
        return p==rhs.p;
    }
    bool operator!=(const FixArrIterator& rhs) const {
        return p!=rhs.p;
    }
    int& operator*() const {
        return *p;
    }
};

template <typename T, size_t S>
class FixArr
{
    public:
        FixArrIterator<T> begin() {return FixArrIterator<T>(mArr);}
        FixArrIterator<T> end() {return FixArrIterator<T>(&mArr[S]);}

        FixArr() {}
        ~FixArr(){}

        T& operator[](size_t idx)
        {
            return mArr[idx];
        }
        FixArr& operator=(const FixArr& rhs)
        {
            for (size_t i = 0; i < S; ++i)
                mArr[i] = rhs.mArr[i];
            return *this;
        }
        T operator[](size_t idx) const
        {
            return mArr[idx];
        }
        friend ostream& operator<<(ostream& os, const FixArr & a)
        {
            os << "\"";
            for (size_t i = 0; i < S - 1; ++i)
                os << a[i] << ' ';

            if (S > 0)
            os << a[S - 1];

            os << "\"";

            return os;
        }
    protected:
    private:
        T mArr[S];
};

#endif // FIXARR_H
