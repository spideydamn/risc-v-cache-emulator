cmake_minimum_required(VERSION 3.12)

project(
        CacheISA
        VERSION 1.0
        DESCRIPTION "se-comp-arch24"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} ../main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})