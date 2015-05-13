cmake_minimum_required (VERSION 2.6)
project (lab3)
set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")
add_executable(lab3
  test1.cpp
  node.cpp node.h
  threaded_BST.cpp threaded_BST.h
  BiIterator.cpp BiIterator.h)
