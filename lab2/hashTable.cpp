#include <assert.h>
#include <iomanip>

#include "hashTable.h"

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime(int n) {
  if (n == 2 || n == 3) {
    return true;
  }

  if (n == 1 || n % 2 == 0) {
    return false;
  }

  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}

//Return a prime number at least as large as n
int nextPrime(int n) {
  if (n % 2 == 0) {
    n++;
  }

  for (; !isPrime(n); n += 2);

  return n;
}

// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
  : size(nextPrime(table_size)), h(f), nItems(0) {
  hTable = new Item*[size];
  clear(size);
}

//destructor
// IMPLEMENT
HashTable::~HashTable() {
  // do i need to delete every entry in hTable too?
  delete hTable;
}

//Return the load factor of the table
double HashTable::loadFactor() const {
  return (double) nItems / size;
}

//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const {
  int pos = findPosition(key);

  if (pos != NOT_FOUND)
    return hTable[pos]->value;
  
  return NOT_FOUND;
}

//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v) {
  int pos = findPosition(key);

  if (pos != NOT_FOUND) {
    hTable[pos]->value = v;
  } else {
    Item* i = new Item(key, v);
    pos = h(key, size);
    tryInsert(i, pos);
  }

  if (loadFactor() > MAX_LOAD_FACTOR)
    reHash();
}

//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key) {
  int pos = findPosition(key);

  if (pos != NOT_FOUND) {
    delete hTable[pos];
    hTable[pos] = Deleted_Item::get_Item();
    nItems--;
    return true;
  }

  return false; //to be deleted
}

void HashTable::display(ostream& os) {
  if (!hTable) return;

  os << "-------------------------------\n";

  for (int i = 0; i < size; ++i) {
    os << setw(6) << i << ": ";

    if (!hTable[i]) {
      os << "null" << endl;
    } else {
      string key = hTable[i]->key;

      os << "key = " << "\"" << key << "\""
         << setw(12) << "value = " << hTable[i]->value
         << "  (" << h(key, size) << ")" << endl;
    }
  }

  os << endl;
}

//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T) {
  if (!T.hTable) return os;

  for (int i = 0, j = 0; i < T.size && j < T.nItems; ++i) {
    if (T.hTable[i] && T.hTable[i]->value != -1) {
      Item *a = T.hTable[i];

      os << j << ": "
         << "key = " << "\"" << a->key << "\""
         << setw(12) << "value = " << a->value
         << "  (" << T.h(a->key, T.size) << ")" << endl;

      ++j;
    }
  }

  return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash() {
  // copy old values
  Item** oldTable = new Item*[size];
  memcpy(oldTable, hTable, size * sizeof(Item*));
  int oldSize = size;

  // set new params
  size = nextPrime(size * 2);
  // clear hTable
  hTable = new Item*[size];
  clear(size);

  // insert all values from old table to hTable
  for (int i = 0; i < oldSize; ++i) {
    if (oldTable[i]) {
      insert(oldTable[i]->key, oldTable[i]->value);
    }
  }
}

// private function to insert new item at "best" position
void HashTable::tryInsert(Item *i, int pos) {
  if (pos > size)
    tryInsert(i, 0);

  if (!hTable[pos] || hTable[pos] == Deleted_Item::get_Item()) {
    nItems++;
    hTable[pos] = i;
  } else {
    tryInsert(i, pos + 1);
  }
}

int HashTable::findPosition(string key) const {
  for (int i = h(key, size); i < size; ++i)
    if (hTable[i] && hTable[i]->key == key)
      return i;

  return NOT_FOUND;
}

void HashTable::clear(int stop, int start) {
  for (int i = start; i < stop; ++i) {
    hTable[i] = nullptr;
  }
}
