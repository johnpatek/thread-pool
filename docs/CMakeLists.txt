set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

doxygen_add_docs(docs
    ${PROJECT_SOURCE_DIR}/include/thread-pool/thread_pool.h
    "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
    WORKING_DIRECTORY
    "${PROJECT_SOURCE_DIR}/include"
)

doxygen_add_docs(docs
    ${PROJECT_SOURCE_DIR}/include/thread-pool/blocking_queue.h
    "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
    WORKING_DIRECTORY
    "${PROJECT_SOURCE_DIR}/include"
)
