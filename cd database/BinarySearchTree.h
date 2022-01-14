// Binary Search Tree ADT
// Created by A. Student
// Modified by: DongJun Lee

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <string>
#include <iostream>

using std::string;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
public:
    // insert a node at the correct location
    bool insert(const ItemType &item);
    // find a target node
    bool search(const ItemType &target, ItemType &returnedItem) const;
    // find the smallest node
    bool findSmallest(ItemType &returnedItem) const;
    // find the largest node
    bool findLargest(ItemType &returnedItem) const;
     // remove a node if found
    bool remove(const ItemType item);
    // Print all items with same key
    void printAll(const ItemType &target, void visit(ItemType &)) const;

private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// search for target node
	BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, BinaryNode<ItemType>* tgtPtr) const;

    // find the smallest node
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr, ItemType &smallest) const;

    // find the largest node
    BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr, ItemType &smallest) const;
   
    // delete target node from tree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* tgtPtr);
   

};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}

//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType & anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    BinaryNode<ItemType>* tgtPtr = new BinaryNode<ItemType>(anEntry);

    temp = _search(this->rootPtr, tgtPtr);
    if (temp) {
        returnedItem = temp->getItem();
        return true;
    }
    return false;
}

//Wrapper for _delete - Deleteing items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType item)
{
    BinaryNode<ItemType>* tgtPtr = new BinaryNode<ItemType>(item);
    BinaryNode<ItemType>* temp = nullptr;
    
    temp = _remove(this->rootPtr, tgtPtr);
    if (temp) {
        return true;
    }
    return false;
}

// Function to print all items with same key
// Calls search function in order to find all items with same key
template<class ItemType>
void BinarySearchTree<ItemType>::printAll(const ItemType & target, void visit(ItemType &)) const
{
    BinaryNode<ItemType>* tgtPtr = new BinaryNode<ItemType>(target);
    BinaryNode<ItemType>* found = _search(this->rootPtr, tgtPtr);
    
    while (found) {
        ItemType item = found->getItem();
        visit(item);
        found = _search(found->getRightPtr(), tgtPtr);
    }
}

//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    // if the root is null, return new node
    if (!nodePtr) {
        return newNodePtr;
    }
 
    // if the newNode is less than nodePtr, recur for the left subtree
    if (newNodePtr->getItem().getTitle() < nodePtr->getItem().getTitle()) {
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
    }
    // if the newNode is more than the node, recur for the right subtree
    else {
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
    }
 
    return nodePtr;
}
       
//Implementation for the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* tgtPtr) const
{
    BinaryNode<ItemType>* found = nullptr;
    BinaryNode<ItemType>* pWalk = nodePtr;

    if (pWalk) {
        if (tgtPtr->getItem().getTitle() == pWalk->getItem().getTitle())
            return nodePtr;
        else if (tgtPtr->getItem().getTitle() < pWalk->getItem().getTitle())
            return _search(pWalk->getLeftPtr(), tgtPtr);
        else
            return _search(pWalk->getRightPtr(), tgtPtr);
    }

    return found;
}

//Implementation of the delete operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* tgtPtr)
{
    
    // Base case
    if (nodePtr == NULL)
        return nodePtr;
 
    // Recursive calls for ancestors of
    // node to be deleted
    if (nodePtr->getItem().getTitle() > tgtPtr->getItem().getTitle())
    {
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), tgtPtr));
        return nodePtr;
    }
    else if (nodePtr->getItem().getTitle() < tgtPtr->getItem().getTitle())
    {
         nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), tgtPtr));
         return nodePtr;
    }
   
    else if (nodePtr->getItem().getBarcode() != tgtPtr->getItem().getBarcode())
    	{
         nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), tgtPtr));
         return nodePtr;
    	}
    // We reach here when nodePtr is the node
    // to be deleted.

        if (nodePtr->getLeftPtr()== nullptr && nodePtr->getRightPtr() == nullptr)
        {
            // deallocate the memory and update root to null
            delete nodePtr;
            nodePtr = nullptr;
            return  nodePtr;
        }
            // If one of the children is empty
        if (nodePtr->getLeftPtr() == NULL) {
            BinaryNode<ItemType>* temp = nodePtr->getRightPtr();
            delete nodePtr;
            return temp;
        }
        else if (nodePtr->getRightPtr() == NULL) {
            BinaryNode<ItemType>* temp = nodePtr->getLeftPtr();
            delete nodePtr;
            return temp;
        }
       
        // If both children exist
        else {
            BinaryNode<ItemType>* succParent = nodePtr;
     
            // Find successor
            BinaryNode<ItemType>* succ = nodePtr->getRightPtr();
            while (succ->getLeftPtr() != NULL) {
                succParent = succ;
                succ = succ->getLeftPtr();
            }
            
            // Delete successor.  Since successor
            // is always left child of its parent
            // we can safely make successor's right
            // right child as left of its parent.
            // If there is no succ, then assign
            // succ->right to succParent->right
            if (succParent != nodePtr)
                succParent->setLeftPtr(succ->getRightPtr());
            else
                succParent->setRightPtr(succ->getRightPtr());
            
            // Copy Successor Data to nodePtr
            nodePtr->setItem(succ->getItem());
            
            // Delete Successor and return nodePtr
            delete succ;
            return nodePtr;
        }
}


#endif
