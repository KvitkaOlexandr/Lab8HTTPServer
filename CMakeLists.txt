cmake_minimum_required(VERSION 2.8.7)
project(HTTPServerLab)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/server.cpp include/server.h src/languages.cpp include/languages.h)
add_executable(HTTPServerLab ${SOURCE_FILES})
target_link_libraries( HTTPServerLab jansson progbase-cpp progbase)