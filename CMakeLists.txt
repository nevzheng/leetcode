cmake_minimum_required(VERSION 3.19)
project(leetcode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -g")

# Integrate Catch2 Testing Lib
find_package(Catch2 REQUIRED)

add_executable(295 src/295_find_median_from_data_stream.cpp)
target_link_libraries(295 PRIVATE Catch2::Catch2)