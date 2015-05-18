/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/

#include "BiIterator.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr) {}


//Dereferencing operator
ELEMENT& BiIterator::operator*() const {
  return current->value;
}

//Member access operator
ELEMENT* BiIterator::operator->() const {
  return &(current->value);
}

//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const {
  return this->current == it.current;
}

//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const {
  return !(*this == it);
}

//Pre increment operator
BiIterator& BiIterator::operator++() {
  // is there a right sub-tree?
  if (!current->r_thread)
    current = current->right->findMin();
  else
    current = current->right;
  return *this;
}

//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int) {
  //this might be super wrong
  BiIterator *it = this;

  if (!current->r_thread)
    current = current->right->findMin();
  else
    current = current->right;

  return *it;
}

//Pre decrement operator
BiIterator& BiIterator::operator--() {
  // is there a left sub-tree?
  if (!current->l_thread)
    current = current->left->findMax();
  else
    current = current->left;
  return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int) {
  // this might be super wrong

  // create our copy
  BiIterator *it = this;
  // is there a left sub-tree?
  if (!current->l_thread)
    current = current->left->findMax();
  else
    current = current->left;
  return *it;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
