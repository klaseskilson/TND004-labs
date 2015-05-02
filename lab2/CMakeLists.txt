cmake_minimum_required (VERSION 2.6)
project (lab2)
set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")
add_executable(lab2
  test.cpp
  Item.cpp Item.h
  hashTable.cpp hashTable.h)
