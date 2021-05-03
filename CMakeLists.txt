cmake_minimum_required(VERSION 3.2)

# Force C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

project(fractals)

# Add dependencies
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

add_subdirectory(external)

# Add project files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.hpp)

add_executable(fractals ${SOURCES} ${HEADERS})

target_link_libraries(fractals Qt5::Widgets Qt5::PrintSupport qcustomplot)
