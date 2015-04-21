cmake_minimum_required (VERSION 2.6)
project (lab1)
set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")
add_executable(lab1
  main.cpp
  set.cpp set.h)
