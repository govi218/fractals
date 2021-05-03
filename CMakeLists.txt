cmake_minimum_required(VERSION 3.2)

# Force C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project name
project(fractals)

set(SOURCES ${CMAKE_SOURCE_DIR}/main.cpp)
# set(HEADERS ${CMAKE_SOURCE_DIR}/*.hpp)

# target_link_libraries()

add_executable(fractals ${SOURCES} ${HEADERS})
