cmake_minimum_required(VERSION 3.25)
project(OBJEKTINIO_EGZAMINAS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main src/main.cpp src/funkcijos.cpp)