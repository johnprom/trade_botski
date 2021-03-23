cmake_minimum_required(VERSION 3.1)
project(BotskiTrading CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(BotskiTrading main.cpp)
