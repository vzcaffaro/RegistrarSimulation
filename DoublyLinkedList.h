#include "DoublyNode.h"
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

template <class T>
class DoublyLinkedList
{
public:
        DoublyNode<T> *front;
        DoublyNode<T> *back;
        unsigned int size;

        DoublyLinkedList();
        ~DoublyLinkedList();

        void insertBack(T d);
        void insertFront(T d);
        T removeFront();
        bool isEmpty();
        T peek();

};


template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    size=0;
    front=NULL;
    back=NULL;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    DoublyNode<T> *curr = front;
	while (curr != NULL)
	{
		DoublyNode<T> *garbage = curr;
		curr = curr->next;
		curr->prev = NULL;
		delete garbage;
	}
	curr = NULL;
	delete front;
	delete back;

    cout << "object deleted" << endl;
}


template <class T>
T DoublyLinkedList<T>::removeFront()
{
    if(size==0)
    {
        cout<<"Cannot remove from an empty list"<<endl;
        throw -1;
    }

    DoublyNode<T> *ft = front;

    if(front == back)
    {
        back = NULL;
    } else {
        front->next->prev = NULL;
    }
    T temp = front->data; //here was the problem
    front = front->next;
    ft->next = NULL;
    delete ft;
    size--;

    return temp;

}

template <class T>
T DoublyLinkedList<T>::peek()
{
    return front->data;
}

template <class T>
void DoublyLinkedList<T>::insertBack(T d)
{
    DoublyNode<T> *node = new DoublyNode<T>(d);
    if(size==0)
    {
        front = node;
    } else {
        node->prev=back;
        back->next=node;
    }
    back=node;
    ++size;

}

template <class T>
void DoublyLinkedList<T>::insertFront(T d)
{
    DoublyNode<T> *node = new DoublyNode<T>(d);
    if(size==0)
    {
        back = node;
    } else {
        node->next=front;
        front->prev=node;
    }
    front=node;
    ++size;

}


template <class T>
bool DoublyLinkedList<T>::isEmpty()
{
    if(size==0)
        return true;
    else
        return false;
}
