/** ADT Stack implementation.
    @file Stack.hpp  */
#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

#include "abstract_stack.hpp"
#include "Node.hpp"

template<typename T>
class Stack: public AbstractStack<T>
{  
public:
  /** Stack constructor
   *  creates an empty stack
   */
  Stack();

  /** Stack destructor. Must delete any allocated memory. */
  virtual ~Stack();
  
  /** This is the copy constructor. It make a copy of the parameter.  It is also used by the operator= in the copy-swap paradigm.
      @param rhs - the Stack we are copying during construction
  */
  Stack(const Stack& rhs );

  /** This is the assignment operator. It uses the copy-swap paradigm to create a copy of the parameter
      @param rhs - the Stack we are assigning to this
      @return a reference to the Stack that was copied into, a.k.a. *this
  */
  Stack& operator=( Stack rhs ) noexcept;

  /** Returns the number of items on the stack.
      @return The integer number of items on the stack. */
  std::size_t size() const;

  /** Determines whether this stack is empty.
      @return True if the stack has no items, or false if not. */
  bool isEmpty() const;

  /** Pushes a new entry onto the top of the stack.
      @post  If successful, newItem is on the top of the stack.
      @param newItem  The item (of datatype T) to be pushed on top of the stack.
      @return  True if insert was successful, or false if not. */
  bool push(const T& newItem);

  /** Pops the top item off of the stack. The stack size is decreased by 1.
      @return  True if successful, or false otherwise. */
  bool pop();

  /** Returns the top item off of the stack without removing it. The stack size
      stays the same.
      @return  Item of T that was on the top of the stack. 
      Throws an exception of type range_error if the stack is empty. */
  const T& peek() const throw(std::range_error);

  /** Removes the top item of the stack and returns it.
      @return  Item of T that was on the top of the stack. 
      Throws an exception of type range_error if the stack is empty. */
  T peekPop() throw(std::range_error);

  /** Deletes all entries on the stack.
      @post  Stack contains no items, and the size of the stack is 0. */
  void clear();

  /** This is the swap method. It will swap the internals of the two stacks.  Notably it is used in the operator= to 
      implement the copy swap paradigm.  It is also used by other C++ paradigms.
      @param lhs - the Stack on the left...Left Hand Side (lhs)
      @param rhs - the Stack on the right...Right Hand Side (rhs)
  */
  void swap(Stack& lhs, Stack& rhs);
  
private:
  /** Number of items on the stack
   */
  std::size_t n;

  /** Stack entries
   */
  Node<T> * topPtr;
}; // end Stack

#include "Stack.txx"
#endif

