CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
project(transport_system)

include_directories(include)

set(SOURCES
    src/main.cpp
)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14 -Wall -Werror")

add_executable(transport_system ${SOURCES})
target_link_libraries(transport_system pthread ncurses)
