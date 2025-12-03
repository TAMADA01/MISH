cmake_minimum_required(VERSION 3.28)
project(com_port_lesson)

include(env.cmake)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)
    add_definitions(-DWINVER=0x0A00)

    add_definitions(-D_WIN32)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package (Boost REQUIRED)

file(GLOB_RECURSE SRC
        src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

# Если библиотека найдена, то
if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
    target_link_libraries (${PROJECT_NAME}  ${Boost_LIBRARIES}) # подключаем библиотеку
endif ()

