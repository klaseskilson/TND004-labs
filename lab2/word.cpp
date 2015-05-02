/*
  Name: hashTable.h
  Author: Aida Nordman
  Course: TND004, Lab 2
  Description: test program for class HashTable
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "hashTable.h"

using namespace std;

//A simple hash function
unsigned my_hash(string s, int tableSize) {
  unsigned hashVal = 0;

  for(unsigned i = 0; i < s.length(); i++) {
    hashVal += s[i];
  }

  hashVal %= tableSize;

  return hashVal;
}

bool is_ok_char(char &c) {
  return ispunct(c) && c != '\'';
}

void to_lower(char &c) {
  c = tolower(c);
}

void clean_punct(string& s) {
  for_each(s.begin(), s.end(), to_lower);
  s.erase(remove_if(s.begin(), s.end(), is_ok_char), s.end());
}


int main() {
  const int TABLE_SIZE = 7;
  HashTable table(TABLE_SIZE, my_hash);

  string filename = "test_file1.txt", word = "";
  //cout << "Enter filename: ";
  //cin >> filename;

  ifstream readFile;
  readFile.open(filename);

  if (!readFile.is_open()) {
    cout << "Could not read file '" << filename << "'!";
    return -1;
  }

  while (readFile >> word) {
    clean_punct(word);
    // KOLLA SÅ ATT DEN INTE FÖRSÖKER INFOGA PÅ POSITION 7 som inte finns NÄR DEN KOMMER TILL THE
    cout << endl << endl << word << endl;
    table.display(cout);
    table[word]++;
    table.display(cout);
  }

  cout << table;

  return 0;
}
