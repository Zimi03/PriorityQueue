cmake_minimum_required(VERSION 3.27)
project(PriorityQueue)

set(CMAKE_CXX_STANDARD 20)

add_library(app_libs INTERFACE)
target_include_directories(app_libs INTERFACE libs/)

add_executable(app "src/main.cpp"
        src/Structures/PriorityValueOrderMap.hpp
        src/Queues/PriorityQueueList.hpp
        "src/Structures/List(head).hpp"
        src/Structures/INode.h
        src/Structures/head.hpp
        src/Structures/node.hpp)
target_link_libraries(app app_libs)
target_include_directories(app INTERFACE src/Structures src/Queues src/Tools src/Lists)
