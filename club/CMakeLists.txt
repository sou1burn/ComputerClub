cmake_minimum_required(VERSION 3.20)
project(club)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_compile_options(-Wall -Wextra -Wpedantic -finput-charset=UTF-8 -fexec-charset=UTF-8)

set(CLUB_SOURCES club.cpp
        club.h)

add_library(CLUB ${CLUB_SOURCES})

target_include_directories(CLUB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

target_link_libraries(CLUB PUBLIC UTILS CLIENT TABLE)