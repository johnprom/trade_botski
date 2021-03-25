cmake_minimum_required(VERSION 3.1)
project(BotskiTrading CXX)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(BotskiTrading main.cpp)
target_link_libraries(BotskiTrading ${CONAN_LIBS})
