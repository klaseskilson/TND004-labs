cmake_minimum_required (VERSION 2.6)
project (lab4b)
set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")
add_executable(lab4b
  main.cpp
  dsets.cpp dsets.h
  edge.cpp edge.h
  graph.cpp graph.h
  heap.h
  list.cpp list.h)
