#ifndef SHARED_PTR
#define SHARED_PTR
#include <iostream>

template <typename T>
class SharedPtr
{
private:
/*
    @attr ptr(pointer to T): a pointer to the given position
    @attr count(pointer to int): the number of instances pointing to a same place
*/
    T *ptr;
    int *count;
public:
    // default constructor
    SharedPtr() : ptr(nullptr), count(nullptr) {}

    // constructor
    explicit SharedPtr(T *pointer) : ptr(pointer) 
    {
        if (pointer) count = new int, *count = 1;
        else count = nullptr;
    }

    // copy constructors
    SharedPtr(const SharedPtr &other) : ptr(other.ptr), count(other.count)
    {
        if(this == &other) return;
        if (count) (*count)++;
    }
    
    // operator =
    SharedPtr& operator = (const SharedPtr &other)
    {
        if (this == &other) return *this;
        this -> reset();
        ptr = other.ptr, count = other.count;
        if (count) (*count)++;
        return *this;
    }

    int use_count() { return count ? *count : 0; }
    T* get() const { return ptr; }

    // operator * and operator ->
    T* operator -> () { return ptr; }
    T& operator * () { return *ptr; }

    // operator bool
    operator bool() const { return ptr; }

    // reset()
    void reset()
    {
        if (ptr)
        {
            if (*count > 1)
                (*count)--;
            else
            {
                delete ptr;
                delete count;
            }
            ptr = nullptr, count = nullptr;
        }
    }
    void reset(T* pointer)
    {
        if (ptr == pointer) return;
        reset();
        ptr = pointer;
        if (pointer) count = new int, *count = 1;
    }
    // deconstructor
    ~SharedPtr() { reset(); }
};

template <typename T, typename ... Args>
SharedPtr<T> make_shared(Args&&... args)
{
    return SharedPtr(new T(std :: forward<Args>(args) ...));
}
#endif