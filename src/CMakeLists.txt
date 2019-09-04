add_library(thread-pool-dynamic SHARED thread_pool.cpp)

target_include_directories(thread-pool-dynamic PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(thread-pool-dynamic ${CMAKE_THREAD_LIBS_INIT})

add_library(thread-pool-static STATIC thread_pool.cpp)

target_include_directories(thread-pool-static PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(thread-pool-static ${CMAKE_THREAD_LIBS_INIT})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


install(TARGETS thread-pool-dynamic thread-pool-static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
        
install(FILES ${PROJECT_SOURCE_DIR}/include/thread-pool/thread_pool.hpp 
        DESTINATION include/thread-pool/thread_pool.hpp)

install(FILES ${PROJECT_SOURCE_DIR}/include/thread-pool/blocking_queue.hpp 
        DESTINATION include/thread-pool/blocking_queue.hpp)