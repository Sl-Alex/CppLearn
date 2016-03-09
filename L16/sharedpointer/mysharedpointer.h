#ifndef MYSHAREDPOINTER_H
#define MYSHAREDPOINTER_H

#include <iostream>

#define PTR_DEBUG

using namespace std;

template <typename T>
class MySharedPointer
{
public:
    MySharedPointer(T * obj = NULL, bool isArray = false)
        :mObj(obj),
        mArray(isArray)
    {
#ifdef PTR_DEBUG
        cout << "created" << endl;
#endif
    }

    ~MySharedPointer()
    {
        deletePointer();
    }

    T* operator->() { return mObj; }
    T& operator* () { return *mObj; }
    MySharedPointer& operator=(const MySharedPointer& obj) {
        mRefCount++;
#ifdef PTR_DEBUG
        cout << "operator=" << endl;
        cout << "mRefCount = " << mRefCount << endl;
#endif
        mObj = obj.mObj;
        mArray = obj.mArray;
        return *this;
    }
    T& operator[](size_t index){
        return mObj[index];
    }

private:
    void deletePointer(void)
    {
        if (mRefCount)
            mRefCount--;

#ifdef PTR_DEBUG
            cout << "mRefCount-- = " << mRefCount << endl;
#endif
        if (mRefCount > 0)
            return;

        if (mArray)
        {
#ifdef PTR_DEBUG
            cout << "deleted[]" << endl;
#endif
            delete[] mObj;
        }
        else
        {
#ifdef PTR_DEBUG
            cout << "deleted" << endl;
#endif
            delete mObj;
        }
        mObj = NULL;
    }

    T * mObj;
    bool mArray;
    static int mRefCount;
};

template<typename T> int MySharedPointer<T>::mRefCount = 1;

#endif // MYSHAREDPOINTER_H
