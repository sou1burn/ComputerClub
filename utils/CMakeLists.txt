cmake_minimum_required(VERSION 3.20)
project(utils)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_compile_options(-Wall -Wextra -Wpedantic -finput-charset=UTF-8 -fexec-charset=UTF-8)

set(UTILS_SOURCES utils.cpp
        utils.h)

add_library(UTILS STATIC ${UTILS_SOURCES})

target_include_directories(UTILS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
