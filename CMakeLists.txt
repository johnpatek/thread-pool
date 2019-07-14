
cmake_minimum_required(VERSION 2.8.0)

project(thread-pool)

set(CMAKE_CXX_STANDARD 11)

add_library(thread-pool thread_pool.cpp)