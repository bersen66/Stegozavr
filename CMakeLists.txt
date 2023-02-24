cmake_minimum_required(VERSION 3.5)
project(Stegozavr)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

include(third_party/userver/cmake/SetupEnvironment.cmake)
include(GNUInstallDirs)

add_subdirectory(third_party/userver)


add_library(
    BACKEND OBJECT
        src/stegozavr/api/handler.cpp
    )

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(BACKEND PUBLIC userver-core)
target_link_libraries(${PROJECT_NAME} PRIVATE BACKEND)

