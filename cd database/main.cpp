/***
   CIS22C Lab 8.14 BT <-- BST ADT
   By DongJun Lee
   Using Code Blocks
   5/16/21
***/

#include "BinarySearchTree.h"  // BST ADT
#include "HashTable.h"
#include "Stack.h"
#include "CD.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstring>

//#include <bits/stdc++.h>

using namespace std;

void buildBST(const string &filename, BinarySearchTree<CD> &);
void hDisplay(CD &);
void titleSearchManager(const BinarySearchTree<CD> &);
void displayManager(const BinarySearchTree<CD> &);
int key_to_index(const CD &key, int size);
void barcodeSearchManager(HashTable<CD>& list);
void buildHash(const string &filename, HashTable<CD> &);
void removeManager(HashTable<CD>&, BinarySearchTree<CD>&, Stack<CD>&);
void undoDelete(Stack<CD> &, HashTable<CD> &, BinarySearchTree<CD>&);
void insert(BinarySearchTree<CD> &bst,HashTable<CD> &hash);

/*
void vDisplay(CD &);
void iDisplay(CD &, int);
*/

int main()
{
    string filename = "Classical_CD_Repository.txt";
    string outFileName = "HashReport.txt";
    BinarySearchTree<CD> bst;
    HashTable<CD> hash;
    Stack<CD> stack;
    
    
    
    buildBST(filename, bst);
    buildHash(filename,hash);
    hash.display();

    cout << "MENU OPTIONS" << endl;
    cout << "============" << endl << endl;
    cout << "1: Display Manager" << endl;
    cout << "2: Remove Manager" << endl;
    cout << "3: Search Manager(Barcode)" << endl;
    cout << "4: Search Manager(Title)" << endl;
    cout << "5: Undo" << endl;
    cout << "6: Write Data to the File" << endl;
    cout << "7: Stats" << endl;
    cout << "8: Insert" << endl;
    cout << "9: Help" << endl;
    
    cout << endl;
    
    

    int option;
    cout << "Enter your options ['O' to quit/'9' for help (Back to menu)]: ";
    cin >> option;
    cout << endl;
    
    while (option != 0) {
    if (option == 1) {
    displayManager(bst);
    } else if (option == 2){
        cin.ignore();
        removeManager(hash,bst,stack);
    }else if (option == 3){
        cin.ignore();
        barcodeSearchManager(hash);
    }else if (option == 4){
        cin.ignore();
        titleSearchManager(bst);
    }else if (option == 5){
        undoDelete(stack, hash, bst);
    }else if (option == 6){
        hash.writeToFile(outFileName);
        stack.~Stack<CD>();
    }else if (option == 7){
        hash.statistics();
    }else if (option == 8){
        insert(bst, hash);
    }else if (option == 9){
        cout << "MENU OPTIONS" << endl;
        cout << "============" << endl << endl;
        cout << "1: Display Manager" << endl;
        cout << "2: Remove Manager" << endl;
        cout << "3: Search Manager(Barcode)" << endl;
        cout << "4: Search Manager(Title)" << endl;
        cout << "5: Undo" << endl;
        cout << "6: Write Data to the File" << endl;
        cout << "7: Stats" << endl;
        cout << "8: Insert" << endl;
        cout << "9: Help" << endl;
    }
        
        cout << endl;
        cout << "Enter your options ['O' to quit/'9' for help (Back to menu)]: ";
        cin >> option;
        cout << endl;
    }
    hash.display();
    
}


/* Write your code here */
/*
 This function reads data about colleges from a file and inserts them
 into a sorted linked list. The list is sorted in ascending order by code
*/
void buildBST(const string &filename, BinarySearchTree<CD> &list)
{
    ifstream fin(filename);
    //cout << "Reading data from \"" << filename << "\"";

    if(!fin)
    {
        cout << "Error opening the input file: \""<< filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    string line;

    while (getline(fin, line))
    {
       string barcode, composer, title, conductor;
       int year;

       stringstream temp(line);   // create temp with data from line
       temp >> barcode;              // read from temp
       temp >> composer;
        temp>>std::ws;
       getline(temp, title, ';');// stop reading name at ';'
        temp>>std::ws;
       getline(temp, conductor, ';');  // stop reading name at ';'
       temp >> year;
       // create a College object and initialize it with data from file
       CD aCD(barcode, composer, title, conductor, year);
       list.insert(aCD);
    }

    fin.close();
}


void buildHash(const string &filename, HashTable<CD> &list){
    ifstream fin(filename);
    //cout << "Reading data from \"" << filename << "\"";

    if(!fin)
    {
        cout << "Error opening the input file: \""<< filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    string line;

    while (getline(fin, line))
    {
       string barcode, composer, title, conductor;
       int year;

       stringstream temp(line);   // create temp with data from line
       temp >> barcode;              // read from temp
       temp >> composer;
        temp>>std::ws;
       getline(temp, title, ';');// stop reading name at ';'
        temp>>std::ws;
       getline(temp, conductor, ';');  // stop reading name at ';'
       temp >> year;
       // create a College object and initialize it with data from file
       CD aCD(barcode, composer, title, conductor, year);
        list.insert(aCD);
    }

    fin.close();
    
    while (list.getLoadFactor() >= 0.75) {
        list.rehash();
    }
}


void displayManager(const BinarySearchTree<CD> & list){

    string action;
    cout << "Display inorder by Title [Y/N]: ";
    cin >> action;
    char option = toupper(action[0]);
    cout << endl;
    if(option == 'Y')
    {   cout << left << setw(12) << "Barcode" << "   ";
        cout << left << setw(15) << "Composer" << "   ";
        cout << left << setw(24) << "Title" << "    ";
        cout << left << setw(23) << "Conductor"<< "    ";
        cout << right << setw(4) << "Year" << endl;

        cout << left << setw(12) << "=======" << "   ";
        cout << left << setw(15) << "========" << "   ";
        cout << left << setw(24) << "=====" << "    ";
        cout << left << setw(23) << "========="<< "    ";
        cout << right << setw(4) << "====" << endl << endl;
        
        list.inOrder(hDisplay);
    }
}



void titleSearchManager(const BinarySearchTree<CD> &list){

    string title;
    CD a, item;
    string bar;


    cout << "Search By Title" << endl;
    cout << "===============" << endl << endl;

    cout << "Enter Title or Q to quit: ";
    getline(cin, title);
    cout << endl;

    while(toupper(title[0]) != 'Q')
    {
        a.setTitle(title);

        if(list.search(a,item))
        {
            cout << left << setw(12) << "Barcode" << "   ";
            cout << left << setw(15) << "Composer" << "   ";
            cout << left << setw(24) << "Title" << "    ";
            cout << left << setw(23) << "Conductor"<< "    ";
            cout << right << setw(4) << "Year" << endl;

            cout << left << setw(12) << "=======" << "   ";
            cout << left << setw(15) << "========" << "   ";
            cout << left << setw(24) << "=====" << "    ";
            cout << left << setw(23) << "========="<< "    ";
            cout << right << setw(4) << "====" << endl << endl;
            
            list.printAll(a,hDisplay);
        } else
        {
            cout << "Title \"" << title << "\" was not found in this list." << endl;
        }

        cout << endl;
        cout << "Enter Title or Q to quit: ";
        getline(cin, title);
    }
}


void barcodeSearchManager(HashTable<CD>& list){

    cout << "Search by Barcode" << endl;
    cout << "=================" << endl << endl;

    string barcode;

    cout << "Enter barcode or Q to quit: ";
    getline(cin, barcode);
    cout << endl;

    while (toupper(barcode[0]) != 'Q' )
    {
        CD found, key(barcode, " ", " "," ",-1);

        if (list.search(found, key) != -1){
            
            cout << left << setw(12) << "Barcode" << "   ";
            cout << left << setw(15) << "Composer" << "   ";
            cout << left << setw(24) << "Title" << "    ";
            cout << left << setw(23) << "Conductor"<< "    ";
            cout << right << setw(4) << "Year" << endl;

            cout << left << setw(12) << "=======" << "   ";
            cout << left << setw(15) << "========" << "   ";
            cout << left << setw(24) << "=====" << "    ";
            cout << left << setw(23) << "========="<< "    ";
            cout << right << setw(4) << "====" << endl << endl;
            cout << found;
        }
        else
        {
            cout << endl << barcode << " not found!" << endl;
        }
        cout << endl;
        cout << "Enter barcode or Q to quit: ";
        getline(cin, barcode);
    }
}


void removeManager(HashTable<CD>& list, BinarySearchTree<CD>& bst, Stack<CD>& stack){
    string barcode;

    cout << "Remove CD" << endl;
    cout << "=========" << endl << endl;

    cout << "Enter barcode or Q to quit: ";
    getline(cin, barcode);
    cout << endl;

    while (toupper(barcode[0]) != 'Q' )
    {
        CD itemOut, key(barcode, " ", " "," ",-1);

        /*
         insert barcode (unique) to delete from the hash
         if found get the title of the barcode and delete the title with the
         samebarcode from the bst.
         push both to stack
         use undo function to reinsert in hash and bst.
         */

        if (list.remove(itemOut, key))
        {
            cout << itemOut.getBarcode() << "- deleted" << endl;
            stack.push(itemOut);
            bst.remove(itemOut);
        }
        else
        {
            cout << endl << barcode << " not found!" << endl;
        }
        cout << endl;
        cout << "Enter barcode or Q to quit: ";
        getline(cin, barcode);
    }
}

void undoDelete(Stack<CD> & stack, HashTable<CD> & hash, BinarySearchTree<CD> & bst){

    cout << "Undo Delete" << endl;
    cout << "===========" << endl << endl;

    CD a;
    char option;
    cout << "Undo Delete [Y/N]: " << endl;
    cin >> option;
    if(stack.isEmpty()) {
        cout << "Error: Remove an Item First" << endl;
    } else if (option == 'y'|| option == 'Y'){
        while(!stack.isEmpty()){
            a = stack.pop();
            hash.insert(a);
            bst.insert(a);
        }
    }
}

void insert(BinarySearchTree<CD> &bst,HashTable<CD> &hash)
{

    string barcode, conductor, title, composer;
    int year;
    char option;

    cout << "Insert Item" << endl;
    cout << "===========" << endl << endl;

    cout << "Insert Item[Y/N]: ";
    cin >> option;
    cout << endl;

    while (option == 'y' || option == 'Y')
    {
        cout << "Enter Barcode: ";
        cin >> barcode;
        cout << "Enter Composer: ";
        cin >>composer;
        cout << "Enter title: ";
        cin.ignore();
        getline(cin,title);
        cout << "Enter conductor: ";
        getline(cin,conductor);
        cout << "Enter year: ";
        cin >> year;

        CD a(barcode,composer,title,conductor,year);

        if (hash.insert(a)){
            bst.insert(a);
            cout << endl <<"Item Added" << endl << endl;

            cout << left << setw(12) << "Barcode" << "   ";
            cout << left << setw(15) << "Composer" << "   ";
            cout << left << setw(24) << "Title" << "    ";
            cout << left << setw(23) << "Conductor"<< "    ";
            cout << right << setw(4) << "Year" << endl;

            cout << left << setw(12) << "=======" << "   ";
            cout << left << setw(15) << "========" << "   ";
            cout << left << setw(24) << "=====" << "    ";
            cout << left << setw(23) << "========="<< "    ";
            cout << right << setw(4) << "====" << endl << endl;

            cout << a << endl;

        }
        else
        {
        cout << "Duplicate barcode could not be added" << endl;
        }
        cout << "Insert Item[Y/N]: ";
        cin >> option;
        cout << endl;
    }
}

void hDisplay (CD &item)
{
    cout << left << setw(12) << item.getBarcode() << "   ";
    cout << left << setw(15) << item.getComposer() << "   ";
    cout << left << setw(24) << item.getTitle() << "    ";
    cout << left << setw(23) << item.getConductor()<< "    ";
    cout << right << setw(4) << item.getYear() << endl;
}


