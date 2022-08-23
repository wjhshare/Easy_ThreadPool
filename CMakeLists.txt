cmake_minimum_required(VERSION 3.15)
project(Easy_THreadPool)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE “Debug”)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(Easy_ThreadPool main.cpp ThreadPool.cpp)
target_link_libraries(Easy_ThreadPool pthread)