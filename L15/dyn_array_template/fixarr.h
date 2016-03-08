#ifndef FIXARR_H
#define FIXARR_H

#include <iostream>
using namespace std;

template <typename T, size_t S>
class FixArr
{
    public:
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
