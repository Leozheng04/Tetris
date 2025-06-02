cmake_minimum_required(VERSION 3.31.3)
project(PONG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)      
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF) 

find_package(raylib REQUIRED)
add_executable(${PROJECT_NAME} pong.cpp)

target_link_libraries(${PROJECT_NAME} raylib)
