cmake_minimum_required(VERSION 3.5)
project(Stegozavr)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
message("MODULE PATH: ${CMAKE_MODULE_PATH}")

include(third_party/userver/cmake/SetupEnvironment.cmake)
include(GNUInstallDirs)

add_subdirectory(third_party/userver)


add_library(
  BACKEND OBJECT
  src/stegozavr/api/v1/encode.cpp
  src/stegozavr/api/v1/decode.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(BACKEND PUBLIC userver-core)
target_link_libraries(${PROJECT_NAME} PRIVATE BACKEND)

#TESTING:
#add_subdirectory(tests)
