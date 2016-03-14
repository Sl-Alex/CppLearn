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
        pRefCount = new size_t;
        *pRefCount = 1;
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
        deletePointer();
        pRefCount = obj.pRefCount;
        (*pRefCount)++;
#ifdef PTR_DEBUG
        cout << "operator=" << endl;
        cout << "mRefCount = " << *pRefCount << endl;
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
        if (*pRefCount)
            (*pRefCount)--;

#ifdef PTR_DEBUG
            cout << "mRefCount-- = " << *pRefCount << endl;
#endif
        if ((*pRefCount) > 0)
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
        delete pRefCount;
        mObj = NULL;
    }

    T * mObj;
    bool mArray;
    size_t * pRefCount;
};

#endif // MYSHAREDPOINTER_H
