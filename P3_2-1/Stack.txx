#include "Stack.hpp"
#define tnp nullptr

/** Stack constructor
   *  creates an empty stack
   */
template <typename T>
Stack<T>::Stack() {
	n = 0;
	topPtr = tnp;
}

/** Stack destructor. Must delete any allocated memory. */
// STUDENT COMMENTS: Destructor uses the clear() function to 
// clear the contents of the stack that is created by the constructor
template <typename T>
Stack<T>::~Stack() {
	clear();
}

/** This is the copy constructor. It make a copy of the parameter.  It is also used by the operator= in the copy-swap paradigm.
	  @param rhs - the Stack we are copying during construction
  */
  // STUDENT COMMENTS: Copy constructor allows for a new stack to be created and use the same values for the initial stack
template <typename T>
Stack<T>::Stack(const Stack& rhs) {
	this->n = rhs.n;
	Node<T>* newNode = rhs.topPtr;

	// if newNode isn't a null pointer
	if (newNode != tnp) {
		topPtr = new Node<T>(newNode->getItem(), newNode->getNext());
		newNode = newNode->getNext();
		Node<T>* pointyBoy = this->topPtr;

		// while it still continues
		while (newNode != tnp) {
			Node<T>* nextPointyBoy = new Node<T>(newNode->getItem(), newNode);
			newNode = newNode->getNext();
			pointyBoy->setNext(nextPointyBoy);
			pointyBoy = pointyBoy->getNext();
		}
	}

	// if it is a nullptr, then make the head the nullptr.
	else {
		this->topPtr = tnp;
	}
}

/** This is the assignment operator. It uses the copy-swap paradigm to create a copy of the parameter
	  @param rhs - the Stack we are assigning to this
	  @return a reference to the Stack that was copied into, a.k.a. *this
	  // STUDENT COMMENTS: sets the stack as necessary whenever an equalsoperator is usedd: example; s1 = s2
  */
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> rhs) noexcept {
	// using swap function, swapping current object with rhs
	swap((*this), rhs);

	// return the class object
	return *this;
}

/** Returns the number of items on the stack.
	  @return The integer number of items on the stack. */
	  // STUDENT COMMENTS: returns the number of elements in the stack
template<typename T>
std::size_t Stack<T>::size() const {
	return n;
}

/** Determines whether this stack is empty.
	  @return True if the stack has no items, or false if not. */
	  // STUDENT COMMENTS: pretty straightforward...
template<typename T>
bool Stack<T>::isEmpty() const {
	return (topPtr == tnp);
}

/** Pushes a new entry onto the top of the stack.
	  @post  If successful, newItem is on the top of the stack.
	  @param newItem  The item (of datatype T) to be pushed on top of the stack.
	  @return  True if insert was successful, or false if not. */
	  // STUDENT COMMENTS: i- pls read first line tyty
template<typename T>
bool Stack<T>::push(const T& newItem) {
	n++; // increase size

	// create new node
	Node<T>* newNode = new Node<T>(newItem, topPtr);

	// this node will be the new topPtr, as on a stack, item is added to the top
	topPtr = newNode;

	// if the top pointer is equal to nullptr, push returns false
	if (topPtr == tnp) {
		return false;
	}

	// otherwise return true, suggesting item has been pushed
	return true;
}

/** Pops the top item off of the stack. The stack size is decreased by 1.
	  @return  True if successful, or false otherwise. */
	  // STUDENT COMMENTS: pop removes the top item, and returns true if popped.
template<typename T>
bool Stack<T>::pop() {
	// if nullptr, then unable to pop
	if (topPtr == tnp) {
		return false;
	}
	// if only one item
	else if (n == 1) {
		// delete top pointer
		delete topPtr;
		topPtr = tnp;
		n--; //decrease size
		return true;
	}
	//  if there are multiple items
	else if ((topPtr != tnp) && (n != 1)) {
		// similar process, except topPtr = the next item
		Node<T>* newNode = topPtr;
		topPtr = topPtr->getNext();
		newNode->setNext(nullptr);
		delete newNode;
		n--;
		newNode = tnp;

		return true;
	}
}

/** Returns the top item off of the stack without removing it. The stack size
	  stays the same.
	  @return  Item of T that was on the top of the stack.
	  Throws an exception of type range_error if the stack is empty. */
template<typename T>
const T& Stack<T>::peek() const throw(std::range_error) {
	// if null, throw the range error
	if (topPtr == tnp) {
		throw std::range_error("Sin Suerte");
	}
	// otherwise, return the item at the top of the stack
	else if (topPtr != tnp) {
		return topPtr->getItem();
	}

}

/** Removes the top item of the stack and returns it.
	  @return  Item of T that was on the top of the stack.
	  Throws an exception of type range_error if the stack is empty. */
template<typename T>
T Stack<T>::peekPop() throw(std::range_error) {
	// if top = empty, cannot peek/pop
	if (topPtr == tnp) {
		throw std::range_error("Sin Suerte");
	}
	// if only one item in stack
	else if (n == 1) {
		T newNodeItem = topPtr->getItem();
		delete topPtr;
		topPtr = tnp;
		n--;
		return newNodeItem;
	}
	// if multiple items
	else if ((topPtr != tnp) && (n != 1)) {
		Node<T>* newNode = topPtr;
		T newNodeItem = topPtr->getItem();
		topPtr = topPtr->getNext();
		newNode->setNext(nullptr);
		delete newNode;
		newNode = tnp;
		n--;
		return newNodeItem;
	}
}

/** Deletes all entries on the stack.
	  @post  Stack contains no items, and the size of the stack is 0. */
template<typename T>
void Stack<T>::clear() {
	// keep popping till top item isn't null
	while (topPtr != tnp) {
		pop();
	}
}

/*
 * swap method swaps the contents of the two stacks that are available. lhs and rhs are swapped
 * with the both values changed, unlike in copy constructor
*/
template<typename T>
void Stack<T>::swap(Stack& lhs, Stack& rhs) {
	//swap top items for stack
	Node<T>* temp = lhs.topPtr;
	lhs.topPtr = rhs.topPtr;
	rhs.topPtr = temp;

	// swap count size
	int temp2 = lhs.n;
	lhs.n = rhs.n;
	rhs.n = temp2;
}