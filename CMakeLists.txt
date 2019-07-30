cmake_minimum_required(VERSION 2.8)

project(thread-pool)

set(CMAKE_CXX_STANDARD 11)

set(HEADER_SOURCE src/include)

if WIN32
    set(HEADER_DESTINATION "C:/Program Files/thread-pool/include")
    set(LIBRARY_DESTINATION "C:/Program Files/thread-pool/lib")
else()
    set(HEADER_DESTINATION /usr/include)
    set(LIBRARY_DESTINATION /usr/lib)

include_directories(${HEADER_SOURCE})

add_library(thread-pool SHARED src/thread_pool.cpp)

install(TARGETS thread-pool DESTINATION ${LIBRARY_DESTINATION})
install(FILES ${HEADER_SOURCE}/blocking_queue.h DESTINATION ${HEADER_DESTINATION})
install(FILES ${HEADER_SOURCE}/thread_pool.h DESTINATION ${HEADER_DESTINATION})