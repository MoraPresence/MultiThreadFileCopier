cmake_minimum_required(VERSION 3.16)
project(multiThreadFileCopier)

set(CMAKE_CXX_STANDARD 17)

add_executable(multiThreadFileCopier main.cpp consumerFileCopier.cpp consumerFileCopier.h producersFileCopier.cpp producersFileCopier.h)

target_link_libraries(${PROJECT_NAME} stdc++fs)
