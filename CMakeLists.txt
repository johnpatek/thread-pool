
cmake_minimum_required(VERSION 2.8)

project(thread-pool)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/include)

add_library(thread-pool SHARED thread_pool.cpp)

install(TARGETS thread-pool DESTINATION /usr/lib)
install(FILES blocking_queue.h )