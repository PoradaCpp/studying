# CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(TaskTable)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#set(CMAKE_PREFIX_PATH "C:/Qt/5.12.3/mingw73_32")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory("project")
