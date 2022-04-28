cmake_minimum_required(VERSION 3.15.3)
project(multiThreadFileCopier)

set(CMAKE_CXX_STANDARD 17)

add_executable(multiThreadFileCopier main.cpp consumerFileCopier.cpp consumerFileCopier.h producersFileCopier.cpp producersFileCopier.h)

target_link_libraries(${PROJECT_NAME} stdc++fs)

add_compile_options(-pthread)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")