cmake_minimum_required(VERSION 3.28)
project(Test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
        "main.cpp"
        "src/*.cpp"
        "src/figures/*.cpp"
        "src/figures/impls/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
