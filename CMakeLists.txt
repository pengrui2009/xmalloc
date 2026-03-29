cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")


if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OS "LINUX")
    set(DL_LIBRARY "dl")
    set(USE_RT "rt")
    set(OS_CXX_FLAGS "-D__LINUX__ -DNDEBUG -Wl,-rpath=${LOCAL_RPATH}")
    set(OS_LIBS "pthread")
    set(LOG_LIBS ara_log dlt)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

add_library(xmalloc
    SHARED 
    xmalloc
)

target_link_libraries(xmalloc
    pthread
)


#############example code###############
add_executable(xmalloc_test examples/xmalloc_test.c)
include_directories(${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(xmalloc_test
    xmalloc
    pthread
)
