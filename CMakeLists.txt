cmake_minimum_required(VERSION 3.16)
project(DS_WET1)

set(CMAKE_CXX_STANDARD 11)

add_executable(DS_WET1 library1.h AO_Tree_Node.h AO_AVL_Tree.h Employee.h Employee.cpp Company.h Company.cpp Industry.h Industry.cpp library1.cpp main1.cpp)
