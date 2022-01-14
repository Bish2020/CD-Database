//
//  stack.h
//  HW 9.14
//
//  Created by Bishwas Sherchan on 6/8/21.
// This file assists the undo delete function

#ifndef stack_h
#define stack_h

template <class T>
class Stack
{
private:
    // Structure for the stack nodes
    struct StackNode{
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int length;

public:
    // Constructor
    Stack(){top = nullptr; length = 0;}
    
    // Destructor
    ~Stack();
    
    // Stack operations:
    bool push(T n);
    T pop();
    T peek();
    bool isEmpty();
    int getLength(){return length;}
    void getNumValues(int);
    void getEofStack();
};

/*~*~*
   Destructor: deletes all the nodes when called and also updates the length of
 the stack.
 *~**/
template <class T>
Stack<T>::~Stack(){
   StackNode* nodePtr;
   // Position nodePtr at the top of the stack.
   nodePtr = top;
   // Traverse the list deleting each node.
    while (nodePtr){
      top = top->next;
      delete nodePtr;
      nodePtr = top;
       length--;
   }
}

/*~*~*
  Member function push inserts the argument onto the stack and also updates
 length of the stack.
*~**/
template <class T>
bool Stack<T>::push(T item){
   StackNode *newNode; // Pointer to a new node
   // Allocate a new node and store num there.
   newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = item;
   // Update links and counter
   newNode->next = top;
   top = newNode;
   length++;
   return true;
}

/*~*~*
  Member function pop deletes the value at the top of the stack and returns it.
  Assume stack is not empty.
*~**/
template <class T>
T Stack<T>::pop(){
    StackNode* nodePtr;
    T num;
    nodePtr = top;
    num = nodePtr->value;
    top = top->next;
    delete nodePtr;
    nodePtr = nullptr;
    length--;
    return num;
}

/*~*~*
  Member function returns the value of the top of the stack.
*~**/
template <class T>
T Stack<T>::peek(){
    return top->value;
}

/*~*~*
  Member function returns true if the stack is empty or else returns false.
*~**/
template <class T>
bool Stack<T>:: isEmpty(){
    if(top == nullptr){
        return true;
    }
    return false;
}

#endif /* stack_h */
