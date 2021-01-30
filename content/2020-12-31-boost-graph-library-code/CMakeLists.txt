cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

project(bgl-tuto)
set(CMAKE_BUILD_TYPE Release)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(dijkstra-bin dijkstra.cpp)
add_executable(oldproperties-bin oldproperties.cpp)
add_executable(propertymap-map-bin propertymap_map.cpp)
add_executable(propertymap-vector-bin propertymap_vector.cpp)
