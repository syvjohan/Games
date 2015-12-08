#ifndef FRAMEWORK_ARRAY_H
#define FRAMEWORK_ARRAY_H

#include <type_traits>
#include "frameworkdefs.h"

template<typename T>
class Array {
public:
    Array();
    Array(const Array &);
    ~Array();

    const Array& operator=(const Array &);
    const T&  operator[](s32 index) const;
    T&        operator[](s32 index);

    void pushFront(const T &object);
    void pushBack(const T &object);
    
    void remove(const T &object);
    
    void insertAt(const T &object, int index);
    void removeAt(int index);
    void reserve(usize count);
    
    void join(const Array &other);
    
#ifdef FRAMEWORK_USE_MOVE_SEMANTICS
    Array(Array &&);
    const Array& operator=(Array &&);
#endif
    
private:
    void copyFrom(const Array &copy);
    
    T*          mData;
    usize       mSize;
    usize       mCapacity;
};

// ******
// Array::Array
// ******
template<typename T>
Array<T>::Array() {
    mData     = NULL;
    mSize     = 0;
    mCapacity = 0;
}

// ******
// Array::Array(const Array &)
// ******
template<typename T>
Array<T>::Array(const Array &copy) {
    mData     = NULL;
    mSize     = NULL;
    mCapacity = NULL;
    copyFrom(copy);
}


// ******
// Array::~Array
// ******
template<typename T>
Array<T>::~Array() {
    delete[] mData;
    mData     = NULL;
    mCapacity = 0;
    mSize     = 0;
}

// ******
// Array::operator=
// ******
template<typename T>
const Array<T>& Array<T>::operator=(const Array &copy) {
    delete[] mData;
    copyFrom(copy);
    return *this;
}

// ******
// Array::operator[] const
// ******
template<typename T>
const T& Array<T>::operator[](int index) const {
    return mData[index];
}

// ******
// Array::operator[]
// ******
template<typename T>
T& Array<T>::operator[](int index) {
    return mData[index];
}

// ******
// Array::pushFront
// ******
template<typename T>
void Array<T>::pushFront(const T &object) {
    insertAt(object, 0);
}

// ******
// Array::pushBack
// ******
template<typename T>
void Array<T>::pushBack(const T &object) {
    insertAt(object, (int)mSize);
}

// ******
// Array::remove
// ******
template<typename T>
void Array<T>::remove(const T &object) {
    for (usize i = 0; i < mSize; ++i) {
        if (mData[i] == object) {
            removeAt(i);
            return;
        }
    }

    assert(false && "Object is not in array");
}

// ******
// Array::insertAt
// ******
template<typename T>
void Array<T>::insertAt(const T &object, int index) {
    assert(index >= 0 && index <= mSize);
    
}

// ******
// Array::removeAt
// ******
template<typename T>
void Array<T>::removeAt(int index) {
    assert(index >= 0 && index < mSize);

}

// ******
// Array::removeAt
// ******
template<typename T>
void Array<T>::reserve(usize count) {

}

#ifdef FRAMEWORK_USE_MOVE_SEMANTICS

// ******
// Array::Array(Array &&)
// ******
template<typename T>
Array<T>::Array(Array &&move) {
    
}

#endif

#endif // FRAMEWORK_ARRAY_H
