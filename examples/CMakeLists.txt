add_executable(example example.cpp)

target_link_libraries(example thread-pool-static ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(example PUBLIC ${PROJECT_SOURCE_DIR}/include)