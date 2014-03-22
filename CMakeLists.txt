project(dev-wars-sith)

cmake_minimum_required(VERSION 2.6)


include_directories( ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g")

set(dws_SRCS main.cpp)

add_executable(dev-wars-sith ${dws_SRCS})

target_link_libraries(dev-wars-sith)