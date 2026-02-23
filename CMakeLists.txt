cmake_minimum_required(VERSION 3.10)
project(rotation_tool)

find_package(PCL 1.12 REQUIRED)
find_package(yaml-cpp REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(rotate pcd_transform.cpp)
target_link_libraries(rotate ${PCL_LIBRARIES})
target_link_libraries(rotate ${PCL_LIBRARIES} yaml-cpp)