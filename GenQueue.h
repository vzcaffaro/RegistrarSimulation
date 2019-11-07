#include <iostream>
#include "DoublyLinkedList.h"


using namespace std;

template <class T> class GenQueue
{
    public:
        GenQueue(); //default constructor
        ~GenQueue(); //destructor

        //core fuctions
        void insert(T d);
        void insertFront(T d);
        T remove();

        //aux functions
        T peek();
        bool isFull();
        bool isEmpty();



        DoublyLinkedList<T> *myQueue;


};


template <class T>
GenQueue<T>::GenQueue()
{
    myQueue = new DoublyLinkedList<T>();
}

template <class T>
GenQueue<T>::~GenQueue()
{
    delete myQueue;
}

template <class T>
void GenQueue<T>::insert(T d)
{
    myQueue->insertBack(d);
}

template <class T>
void GenQueue<T>::insertFront(T d)
{
    myQueue->insertFront(d);
}

template <class T>
T GenQueue<T>::remove()
{
    return myQueue->removeFront();
}

template <class T>
T GenQueue<T>::peek()
{
    return myQueue->peek();
}

template <class T>
bool GenQueue<T>::isEmpty()
{
    return myQueue->isEmpty();
}
