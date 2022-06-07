cmake_minimum_required(VERSION 3.20)
project(allocator)

set(CMAKE_CXX_STANDARD 23)

add_executable(allocator main.cpp chuncClass.h customAllocatorStrategy.h AllocatorT.h)
