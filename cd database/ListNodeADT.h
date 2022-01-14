// Specification file for the ListNode class
// IDE: Aman Grewal
// Written By: Lance Dela Cruz
// This file assists with the collision resolution
#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>

template <class T>
class ListNode
{
private:
    T data;      // store data
    ListNode *forw;    // a pointer to the next node in the list
public:
    //Constructor
    ListNode(){forw = NULL;}
    ListNode(const T &dataIn, ListNode *forw = NULL){ data = dataIn;}
    
    // setters
    
    // set the forw pointer
    void setNext(ListNode<T>* nextPtr) {forw = nextPtr;}
    void setData(T item) {data = item;}
    
    // getters
    
    // return pointer in the next node
    ListNode *getNext() const {return forw;}
    
    // return data object in the listnode: getData()
    T getData() const{ return data;}

};


#endif
