#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>

using namespace std;

class BigInt
{
    public:

        BigInt(int val = 0);
        BigInt(const BigInt& val);
        ~BigInt();

        enum ConvType{
            CONV_CHAR = 0,
            CONV_UCHAR,
            CONV_SHORT,
            CONV_USHORT,
            CONV_INT,
            CONV_UINT,
            CONV_LONG,
            CONV_ULONG
        };

        // Arithmetic operators ( + - * / % )
        BigInt operator+(const BigInt& rhs) const;
        BigInt operator-(const BigInt& rhs) const;
        BigInt operator*(const BigInt& rhs) const;
        BigInt operator/(const BigInt& rhs) const;
        BigInt operator%(const BigInt& rhs) const;
        BigInt operator+=(const BigInt &rhs);
        BigInt operator-=(const BigInt &rhs);
        BigInt operator*=(const BigInt &rhs);
        BigInt operator/=(const BigInt &rhs);

        // Comparison operators
        bool operator==(const BigInt &rhs) const;
        bool operator!=(const BigInt &rhs) const;
        bool operator> (const BigInt &rhs) const;
        bool operator< (const BigInt &rhs) const;
        bool operator>=(const BigInt &rhs) const;
        bool operator<=(const BigInt &rhs) const;

        BigInt& operator=(const BigInt& other);
        friend ostream& operator<<(ostream& os, const BigInt& val);

        // Unary operators
        friend BigInt operator-(const BigInt& val);
        friend BigInt operator+(const BigInt& val);

        // Operations with integers
        friend BigInt operator*(const int &a, const BigInt &b);
        friend BigInt operator/(const int &a, const BigInt &b);
        friend BigInt operator+(const int &a, const BigInt &b);
        friend BigInt operator-(const int &a, const BigInt &b);

        // Increments/decrements
        BigInt& operator++();   // Pre-increment
        BigInt operator++(int); // Post-increment
        BigInt& operator--();   // Pre-decrement
        BigInt operator--(int); // Post-decrement

        /// @brief Returns true if the number is bigger than the integer;
        bool isConvertable(ConvType c);

    protected:

    private:
        int * mDigits;         // Pointer to the digits memory
        unsigned int mDigCnt;  // Number of digits in the memory
        bool mNegative;        // Is the number negative

        void mRealloc(unsigned int NewCnt); // Allocate another amount of memory
        void mReduce(void);                 // Reduce the number (remove leading zeros)
        int mGetNumber(unsigned int idx) const; // Get the digit at the index. Returns 0 for all indices >= mDigCnt;
        unsigned int mGetLength(int val);   // Get the length of the integer in digits
        void mAppendRight(int val);         // Append the digit to the right, reallocates the memory automatically
        friend int compareArrays(int * arr1, int * arr2, unsigned int sz1, unsigned int sz2); // Compare two BigInt numbers without a sign
        friend BigInt full_division(const BigInt& lhs, const BigInt& rhs, BigInt* remainder); // Complete division algorithm, calculates also a remainder
};

int compareArrays(int * arr1, int * arr2, unsigned int sz1, unsigned int sz2);

#endif // BIGINT_H
