cmake_minimum_required(VERSION 3.20)
project(yadro_testovoe)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(utils)
add_subdirectory(client)
add_subdirectory(table)
add_subdirectory(club)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC UTILS CLIENT TABLE CLUB)

