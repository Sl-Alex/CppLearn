#ifndef MYSHAREDPOINTER_H
#define MYSHAREDPOINTER_H

#include <iostream>

#define PTR_DEBUG

using namespace std;

template <typename T>
class MySharedPointer
{
public:
    typedef void (*MyDeleter)(T *);
    MySharedPointer(T * obj = NULL, MyDeleter f = [](T* a){delete a;})
    {
        pMyPtrState = new MyPtrState;
        pMyPtrState->obj = obj;
        pMyPtrState->refCount = 1;
        pMyPtrState->deleter = f;
#ifdef PTR_DEBUG
        cout << "created" << endl;
#endif
    }

    ~MySharedPointer()
    {
        deletePointer();
    }

    T* operator->() { return pMyPtrState->mObj; }
    T& operator* () { return *(pMyPtrState->mObj); }
    MySharedPointer& operator=(const MySharedPointer& obj) {
        deletePointer();
        pMyPtrState = obj.pMyPtrState;
        pMyPtrState->refCount++;
#ifdef PTR_DEBUG
        cout << "operator=" << endl;
        cout << "mRefCount = " << pMyPtrState->refCount << endl;
#endif
        return *this;
    }
    T& operator[](size_t index){
        return pMyPtrState->obj[index];
    }

private:
    struct MyPtrState{
        T* obj;
        size_t refCount;
        MyDeleter deleter;
    };
    MyPtrState * pMyPtrState;
    void deletePointer(void)
    {
        if (pMyPtrState->refCount)
            pMyPtrState->refCount--;

#ifdef PTR_DEBUG
            cout << "mRefCount-- = " << pMyPtrState->refCount << endl;
#endif
        if (pMyPtrState->refCount > 0)
            return;

        if (pMyPtrState->deleter)
            pMyPtrState->deleter(pMyPtrState->obj);
        else
            delete pMyPtrState->obj;

        delete pMyPtrState;
        pMyPtrState = NULL;
    }
};

#endif // MYSHAREDPOINTER_H
