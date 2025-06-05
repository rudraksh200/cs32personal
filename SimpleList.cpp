//SimpleList.cpp to be completed by the student
//
#include "SimpleList.h"
template <class T>
SimpleList<T>::SimpleList(){
    numElements = 0;
    elements = new T[CAPACITY];
}

template <class T>
SimpleList<T>::~SimpleList(){
    delete[] elements;
}

template <class T>
//T at(int index) const throw (InvalidIndexException);
T SimpleList<T>::at(int index) const{
        if(index < numElements && index >= 0){
            return elements[index];
        }
        throw InvalidIndexException();
}

template <class T>
bool SimpleList<T>::empty() const{
    return (numElements == 0);
}

template <class T>
//T first() const throw (EmptyListException);
//T last() const throw (EmptyListException);
T SimpleList<T>::first() const{
    if(empty()){
        throw EmptyListException();
    }
    return elements[0];
}

template <class T>
T SimpleList<T>::last() const{
    if(empty()){
        throw EmptyListException();
    }
    return elements[numElements-1];
}

template <class T>
int SimpleList<T>::getNumElements() const{
    return numElements;
}

template <class T>
//void insert(T item) throw (FullListException);
void SimpleList<T>::insert(T item){
    if(numElements == CAPACITY){
        throw FullListException();
    }
    elements[numElements] = item;
    numElements++;
}

template <class T>
//void remove(int index) throw (InvalidIndexException, EmptyListException);
void SimpleList<T>::remove(int index){
    if(empty()){
        throw EmptyListException();
    }
    if(!(index < numElements)){
        throw InvalidIndexException();
    }

    if(index == (numElements-1)){
        numElements--;
    }
    else{
        int i = index;
        while(i < numElements-1){
            elements[i] = elements[i+1];
            i++;
        }
        numElements--;
    }
}
