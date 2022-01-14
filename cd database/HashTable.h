// Specification file for the Hash class
// Written By: A. Student
// Changed by: Lance Dela Cruz
// This function deals with the hashtable data structire

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

template<class ItemType>
class HashTable
{
private:
	HashNode<ItemType>* hashAry;
	int hashSize;
    int count;
    int _hash(string key) const;
	
public:
	HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
	HashTable(int n)	{ count = 0; hashSize = n;	hashAry = new HashNode<ItemType>[hashSize]; }
	~HashTable(){ delete [] hashAry; }

	int getCount() const	{ return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const {return static_cast<double>(count) / hashSize; }
    bool isEmpty() const	{ return count == 0; }
    bool isFull()  const	{ return count == hashSize; }
    void display() const;
    
    bool insert( const ItemType &itemIn);
    bool remove( ItemType &itemOut, const ItemType key);
    int  search( ItemType &itemOut, const ItemType key);
    
    
    void statistics();
    void writeToFile(string outFileName);
    void rehash();

};



template<class ItemType>
int HashTable<ItemType>::_hash(string key) const
{
    string firstString, secondString, thirdString;
    int firstInt, secondInt, thirdInt, sum;

    firstString = key.substr(0, 4);
    secondString = key.substr(4, 4);
    thirdString = key.substr(8, 4);

    firstInt = std::stoi(firstString);
    secondInt = std::stoi(secondString);
    thirdInt = std::stoi(thirdString);

    sum = firstInt + secondInt + thirdInt;

    return sum % hashSize;
}




template<class ItemType>
void HashTable<ItemType>::display() const {
    
    for (int i = 0; i < hashSize;  i++) {
        if (hashAry[i].getOccupied() > 0) {
            std::cout << i << ": ";
            hashAry[i].display();
            std::cout << std::endl;
        }
    }
    
}





/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType &itemIn)
{
    // If hashtable is full
    if (count == hashSize)
        return false;
   
    else{
        
        // Hash to get bucket and initialize varibles
        if (itemIn.getBarcode().length() != 12) {
            return false;
            }
         
        int bucket = _hash(itemIn.getBarcode());
        
        // Insert item
        if (hashAry[bucket].insert(itemIn)) {
            
            // Increase count
            count++;
               
            return true;
        }
    return false;
    }
            
}

/*~*~*~*
   Removes the item with the matching key from the hash table
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record
*~**/
template<class ItemType>
bool HashTable<ItemType>::remove(ItemType &itemOut, const ItemType key)
{
    
    if (key.getBarcode().length() != 12) {
        cout << "The barcode must be 12 digits long" << endl;
        return false;
    }
    
    
    int bucket = _hash(key.getBarcode());
    
    // Linear probe hashtable until item found or all items are probed
    if (hashAry[bucket].search(key, itemOut)) {
       
        // Copy data to itemOut and remove data
        hashAry[bucket].remove(key, itemOut);
               
        // Decrement count of items in hashtable
        count--;
        return true;

    }
    
    return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template<class ItemType>
int HashTable<ItemType>::search(ItemType &itemOut, const ItemType key)
{
  
  if (key.getBarcode().length() != 12) {
        return -1;
    }
  
  // Hash the key and initialize other varibles
   int bucket = _hash(key.getBarcode());
        
   // Return no collisions if item found
    if (hashAry[bucket].search(key, itemOut)) {
            return hashAry[bucket].getCollisions();
    }
    return -1;
}

template<class ItemType>
void HashTable<ItemType>::statistics()
{
   
   int totalCollisions = 0;
   int longestList = 0;
   int noLongestLists = 0;
   
   
   for (int i = 0; i < hashSize;  i++) {
        if (hashAry[i].getCollisions() > 0) {
            totalCollisions += hashAry[i].getCollisions();
        }
        if (hashAry[i].getLength() > longestList) {
            longestList = hashAry[i].getLength();
            noLongestLists = 1;
        }
        else if (hashAry[i].getLength() == longestList) {
            noLongestLists++;
        }
            
   }
   
   // Print statistics
    std::cout << "Load Factor: "                    << getLoadFactor() << std::endl;
    std::cout << "Number of Collisions: "           << totalCollisions << std::endl;
    std::cout << "Longest Linked List: "            << longestList     << std::endl;
    std::cout << "Number of longest linked lists: " << noLongestLists  << std::endl;
   
}



template<class ItemType>
void HashTable<ItemType>::writeToFile(string outFileName)
{
    std::ofstream outputFile;
    outputFile.open(outFileName);
     
     for (int i = 0; i < hashSize;  i++) {
        if (hashAry[i].getOccupied() > 0) {
            hashAry[i].writeToFile(outputFile);
        }
    }
    // close file
    outputFile.close();
    
    cout << "Report saved in:  " << outFileName << endl;
}


template<class ItemType>
void HashTable<ItemType>::rehash()
{
   int tempSize = hashSize;
   hashSize = 2 * hashSize;
   HashNode<ItemType> *newHashAry = new HashNode<ItemType>[hashSize];
   int bucket;

   count = 0;

   for ( int i = 0; i < tempSize; i++ )
   {
      if ( hashAry[i].getOccupied() > 0 )
      {
        bucket = _hash(hashAry[i].getBucketKey());
        if (newHashAry[bucket].getOccupied() == 0)
        {
            newHashAry[bucket] = hashAry[i];
            count++;
        }
        }
      }

   delete [] hashAry;
   hashAry = newHashAry;
}
    

#endif // HASHTABLE_H_

