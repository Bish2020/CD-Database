// Specification file for the HashNode class
// Written By: A. Student
// Changed by: Bishwas Shercahn

#ifndef _HASH_NODE
#define _HASH_NODE
#include "LinkedListADT.h" 

// convert to template
template<class ItemType>
class HashNode
{
private:
    LinkedList<ItemType>* list;
    int occupied;
    int noCollisions;

public:
    // constructors
    HashNode() {list = new LinkedList<ItemType>[10]; occupied = 0; noCollisions = 0;}
    
    // common functions
    bool insert(ItemType i) {
        bool status = list->insertNode(i);
        if (status) {
            occupied++;
            if (occupied > 1)
                noCollisions++;
        }
        return status;
    }

    bool search(ItemType key, ItemType& itemOut) {return list->searchList(key, itemOut); }
    void remove(ItemType i, ItemType &dataOut) {list->deleteNode(i, dataOut); occupied--; if (occupied > 0) noCollisions--;}
    void display() {list->displayList();}
    void writeToFile(ofstream& fout) const {list->writeToFile(fout); }
    
    // setters
    void setOccupied(int ocp) {occupied = ocp;}
    void setCollisions(int nCol) {noCollisions = nCol;}
    
    // getters
    
    // returns first barcode in linked list (hashing purposes)
    string getBucketKey() const { return list->getData().getBarcode();}
    
    int getOccupied() const {return occupied;}
    int getCollisions() const {return noCollisions;}
    int getLength() const { return list->getLength();}
}; 

#endif
