cmake_minimum_required(VERSION 3.20)
project(client)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_compile_options(-Wall -Wextra -Wpedantic -finput-charset=UTF-8 -fexec-charset=UTF-8)

set(CLIENT_SOURCES client.cpp
        client.h)

add_library(CLIENT ${CLIENT_SOURCES})


target_include_directories(CLIENT PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/club
)

target_link_libraries(CLIENT PUBLIC UTILS)
