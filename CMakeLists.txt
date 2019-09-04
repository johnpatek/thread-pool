cmake_minimum_required(VERSION 2.8)

project(thread-pool)

if(CMAKE_VERSION VERSION_LESS "3")
    add_definitions(-std=c++11)
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_subdirectory(src)

option(BUILD_DOCS "Generate Doxygen files" OFF)
option(BUILD_EXAMPLES "Build example applications" OFF)
option(BUILD_TESTS "Build unit tests" OFF)

if(BUILD_DOCS)
    find_package(Doxygen)
    message(STATUS "Building docs")
    add_subdirectory(docs)
endif()

if(BUILD_EXAMPLES)
    message(STATUS "Building examples")
    add_subdirectory(examples)
endif()

#if(BUILD_TESTS)
#    include(CTest)
#    message(STATUS "Building tests")
#    add_subdirectory(tests)
#endif()
