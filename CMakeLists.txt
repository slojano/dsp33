cmake_minimum_required(VERSION 3.24)
project(project3)

set(CMAKE_CXX_STANDARD 17)

add_executable(project3 main.cpp item.h warehouse.h orders_dll.cpp orders_dll.h inventory.h order_bst.cpp order_bst.h node_btree.h node_dll.h)
