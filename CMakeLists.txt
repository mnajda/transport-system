CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
project(transport_system)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Simulation.cpp
    src/Train.cpp
    src/TrainStation.cpp
    src/Visualization.cpp
)

find_package(Threads REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++17 -Wall -Werror")

add_executable(transport_system ${SOURCES})
target_link_libraries(transport_system ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES})
