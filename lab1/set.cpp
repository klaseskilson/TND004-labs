/*
 Name: set.cpp
 Author: Aida Nordman, Klas Eskilson
 Course: TND004, Lab 1
 Description: template class to represent a set of elements of type T
 implementation uses a sorted doubly-linked list
 */

#include "set.h"


/*****************************************************
 * Implementation of the member functions            *
 *****************************************************/

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//Default constructor
template<typename T>
Set<T>::Set () {
  init();
}

//conversion constructor
template<typename T>
Set<T>::Set (T n) {
  init();
  insert(tail, n);
}

//Constructor to create a Set from a sorted array
template<typename T>
Set<T>::Set (T a[], int n) {
  init();

  for (int i = 0; i < n; ++i) {
    insert(tail, a[i]);
  }
}

//Copy constructor
template<typename T>
Set<T>::Set (const Set& b) {
  init();

  Node* p = b.head->next;
  while (p->next) {
    insert(tail, p->value);
    p = p->next;
  }
}

//Destructor
template<typename T>
Set<T>::~Set () {
  clear();
  delete head;
  delete tail;
}

//Assignment operator
template<typename T>
const Set<T>& Set<T>::operator= (const Set& b) {
  if (this != &b) {
    Set _copy(b);

    swap(head, _copy.head);
    swap(tail, _copy.tail);
    swap(counter, _copy.counter);
  }
  return *this;
}

//Test whether a set is empty
template<typename T>
bool Set<T>::is_empty () const {
  // compare pointers only
  return head->next == tail;
}

//Test set membership
template<typename T>
bool Set<T>::is_member (T val) const {
  Node* p = head->next;
  while (p->next) {
    if (p->value == val) {
      return true;
    }
    p = p->next;
  }
  return false;
}

//Return number of elements in the set
template<typename T>
int Set<T>::cardinality() const {
  return counter;
}

//Make the set empty
template<typename T>
void Set<T>::clear() {
  Node* p = head->next;
  while (p->next) {
    p = p->next;
    erase(p->prev);
  }
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
template<typename T>
bool Set<T>::operator<= (const Set& b) const {
  return _intersection(b).counter == counter;
}

//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
template<typename T>
bool Set<T>::operator== (const Set& b) const {
  return (*this <= b && b <= *this);
}

//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
template<typename T>
bool Set<T>::operator< (const Set& b) const {
  return *this <= b && !(b <= *this);
}

/****************************************************
 * Private member functions                         *
 ****************************************************/

//Insert a new Node storing val before the Node pointed by p
template<typename T>
Set<T>& Set<T>::insert (Node *p, T val) {
  Node* newNode = new Node(val, p, p->prev);
  p->prev = p->prev->next = newNode;
  //Node wat = *p;
  counter++;
  return *this;
}

//Delete the Node pointed by p
template<typename T>
Set<T>& Set<T>::erase (Node *p) {
  p->prev->next = p->next;
  delete p;
  counter--;
  return *this;
}

//Create an empty Set
template<typename T>
void Set<T>::init () {
  head = new Node();
  tail = new Node();
  head->next = tail;
  tail->prev = head;
  counter = 0;
}

//Display all elements in the Set
template<typename T>
void Set<T>::print (ostream& os) const {
  Node* p = head->next;
  os << "{ ";
  while (p->next) {
    os << p->value << " ";
    p = p->next;
  }
  os << "}";
}

//Set union
//Return a new set with the elements in S1 or in S2 (without repeated elements)
template<typename T>
Set<T> Set<T>::_union (const Set& b) const {
  Set t;

  Node* pa = head->next;
  Node* pb = b.head->next;

  while (pa != tail && pb != b.tail) {
    if (pa->value < pb->value) {
      t.insert(t.tail, pa->value);
      pa = pa->next;
    } else if (pa->value > pb->value) {
      t.insert(t.tail, pb->value);
      pb = pb->next;
    } else {
      t.insert(t.tail, pa->value);
      pa = pa->next;
      pb = pb->next;
    }
  }
  while (pa && pa != tail) {
    t.insert(t.tail, pa->value);
    pa = pa->next;
  }
  while (pb && pb != b.tail) {
    t.insert(t.tail, pb->value);
    pb = pb->next;
  }

  return t;
}

//Set intersection
//Return a new set with the elements in both sets S1 and S2
template<typename T>
Set<T> Set<T>::_intersection (const Set& b) const {
  Set t;

  Node* pa = head->next;
  Node* pb = b.head->next;

  while (pa != tail && pb != b.tail) {
    if (pa->value == pb->value) {
      t.insert(t.tail, pa->value);
      pa = pa->next;
      pb = pb->next;
    } else if(pa->value < pb->value) {
      pa = pa->next;
    } else {
      pb = pb->next;
    }
  }

  return t;
}

//Set difference
//Return a new set with the elements in set S1 that do not belong to set S2
template<typename T>
Set<T> Set<T>::_difference (const Set& b) const {
  Set t;

  Node* pa = head->next;

  while (pa != tail) {
    if (!b.is_member(pa->value)) {
      t.insert(t.tail, pa->value);
    }
    pa = pa->next;
  }

  return t;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
