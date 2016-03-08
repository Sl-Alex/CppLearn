#ifndef MYSCOPEDPOINTER_H
#define MYSCOPEDPOINTER_H

#include <iostream>

#define PTR_DEBUG

using namespace std;

template <typename T>
class MyScopedPointer
{
public:
    MyScopedPointer(T * obj = NULL, bool isArray = false)
        :mObj(obj),
        mArray(isArray)
    {
#ifdef PTR_DEBUG
        cout << "created" << endl;
#endif
    }

    ~MyScopedPointer()
    {
        deletePointer();
    }

    T* operator->() { return mObj; }
    T& operator* () { return *mObj; }
    MyScopedPointer& operator=(const MyScopedPointer& obj) {
#ifdef PTR_DEBUG
        cout << "operator=" << endl;
#endif
        deletePointer();
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
        if (mObj == NULL) return;
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
};

#endif // MYSCOPEDPOINTER_H
