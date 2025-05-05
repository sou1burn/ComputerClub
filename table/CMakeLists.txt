cmake_minimum_required(VERSION 3.20)
project(table)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_compile_options(-Wall -Wextra -Wpedantic -finput-charset=UTF-8 -fexec-charset=UTF-8)

set(TABLE_SOURCES table.cpp
        table.h)

add_library(TABLE ${TABLE_SOURCES})

target_include_directories(TABLE PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/club
)

target_link_libraries(TABLE PUBLIC CLUB)

