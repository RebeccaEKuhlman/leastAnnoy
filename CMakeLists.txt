cmake_minimum_required(VERSION 3.23)
project(leastAnnoy)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCES hw2test.cpp MyGraph.cpp)

add_executable(leastAnnoy hw2test.cpp MyGraph.h MyGraph.cpp)

