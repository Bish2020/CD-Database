// Specification file for the LinkedList class
// Written By: A. Student
// Changed By: Lance Dela Cruz
// IDE: Xcode
// This file assists with the collision resolution

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "ListNodeADT.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
 
 using namespace std;

template <class T>
class LinkedList
{
private:
    ListNode<T> *head;
    int length;

public:
    LinkedList();   // constructor
    ~LinkedList();  // destructor

    // Linked list operations
    int getLength() const {return length;}
    T getData() const {return head->getNext()->getData();}
    
    bool insertNode(const T);
    bool deleteNode(const T &, T &dataout);
    bool searchList(const T &, T &itemOut) const;
    void writeToFile(ofstream& outputFile);
    void displayList() const;
};

//**************************************************
// Constructor
// This function allocates and initializes a sentinel node
//      A sentinel (or dummy) node is an extra node added before the first data record.
//      This convention simplifies and accelerates some list-manipulation algorithms,
//      by making sure that all links can be safely dereferenced and that every list
//      (even one that contains no data elements) always has a "first" node.
//**************************************************
template <class T>
LinkedList<T>::LinkedList()
{
    head = new ListNode<T>; // head points to the sentinel node
    head->setNext(head);
    length = 0;
}

//**************************************************
// The insertNode function inserts a new node in a
// sorted linked list
//**************************************************
template <class T>
bool LinkedList<T>::insertNode(const T dataIn)
{
    ListNode<T> *newNode;  // A new node
    ListNode<T> *pCur;     // To traverse the list
    ListNode<T> *pPre;     // The previous node
    ListNode<T> *pWalk;    // Duplicate node traverser
    
    // Allocate a new node and store num there.
    newNode = new ListNode<T>(dataIn);

    // Initialize pointers
    pWalk = head->getNext();
    pPre = head;
    pCur = head->getNext();

    // Look for duplicate nodes
   while (pWalk && dataIn.getBarcode() == pWalk->getData().getBarcode()) {
        if (dataIn.getBarcode() == pWalk->getData().getBarcode()) {
            return false;
        }
   }
        
    // Insert the new node between pPre and pCur
    pPre->setNext(newNode);
    newNode->setNext(pCur);
    
    
    // Update the counter
    length++;
    
    return true;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory.
//**************************************************

template <class T>
bool LinkedList<T>::deleteNode(const T &target, T &dataout)
{
    ListNode<T> *pCur;       // To traverse the list
    ListNode<T> *pPre;       // To point to the previous node
    bool deleted = false;
    
    // Initialize pointers
    pPre = head;
    pCur = head->getNext();

    // Find node containing the target: Skip all nodes whose gpa is less than the target
    while (pCur != head && pCur->getData() != target)
    {
       pPre = pCur;
       pCur = pCur->getNext();
    }
    
    // If found, delete the node
    if (pCur && pCur->getData().getBarcode() == target.getBarcode())
    {
        pPre->setNext(pCur->getNext());
        dataout = pCur->getData(); 
        delete pCur;
        deleted = true;
        length--;
    }
    return deleted;
}


//**************************************************
// displayList shows the value
// stored in each node of the linked list
// pointed to by head, except the sentinel node
//**************************************************
template <class T>
void LinkedList<T>::displayList() const
{
     ListNode<T> *pCur;  // To move through the list

     // Position pCur: skip the head of the list.
     pCur = head->getNext();

     // While pCur points to a node, traverse the list.
     while (pCur != head)
     {
         // Display the value in this node.
         // pCur->getData().hDdisplay();
         
          std::cout << pCur->getData().getTitle() << " -> " ;
         
         // Move to the next node.
         pCur = pCur->getNext();
    }
    std::cout << std::endl;
}


//**************************************************
// The searchList function looks for a target CD
// in the sorted linked list: if found, returns true
// and copies the data in that node to the output parameter
//**************************************************
template <class T>
bool LinkedList<T>::searchList(const T &target, T &itemOut) const
{
    bool found = false; // assume target not found
    ListNode<T> *pCur;         // To move through the list
    
    // Position pCur: skip the head of the list.
    pCur = head->getNext();
    

    
    // Find location: skip all nodes whose code is less than target
    while (pCur != head && found == false){
        if (pCur->getData().getBarcode() == target.getBarcode()){
            found = true;
            itemOut = pCur->getData();
        }
        else {
            pCur = pCur->getNext();
        }
    }
    return found;
}

//**************************************************
// Write to file
// This function writes list to file
//**************************************************

template<class T>
void LinkedList<T>::writeToFile(ofstream& outputFile)
{
    
    ListNode<T> *pCur;
    
    pCur = head->getNext();

    
    while (pCur != head)
    {
        outputFile << pCur->getData().getBarcode() << "  ";
        outputFile << std::left << setw(16) << pCur->getData().getComposer();
        outputFile << std::left << setw(27) << pCur->getData().getTitle();
        outputFile << std::left << setw(25) << pCur->getData().getConductor();
        outputFile << right << setw(4) << pCur->getData().getYear() << std::endl;
        
        pCur = pCur->getNext();
        
    }

}


//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************
template <class T>
LinkedList<T>::~LinkedList()
{
    ListNode<T> *pCur;     // To traverse the list
    ListNode<T> *pNext;    // To hold the address of the next node
    
    // Position nodePtr: skip the head of the list
    pCur = head->getNext();
    // While pCur is not at the end of the list...
    while(pCur != head)
    {
        // Save a pointer to the next node.
        pNext = pCur->getNext();
        
        // Delete the current node.
        delete pCur;
        
         // Position pCur at the next node.
        pCur = pNext;
    }
    
    delete head; // delete the sentinel node
}



#endif

