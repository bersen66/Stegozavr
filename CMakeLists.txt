cmake_minimum_required(VERSION 3.5)
project(Stegozavr)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
message("MODULE PATH: ${CMAKE_MODULE_PATH}")

include(third_party/userver/cmake/SetupEnvironment.cmake)
include(GNUInstallDirs)

add_subdirectory(third_party/userver)

# INCLUDING STEGANOGRAPHIC ENGINE
include_directories(third_party/in_image_hider)
include_directories(third_party/png-plusplus)

add_library(
        BACKEND OBJECT
        src/stegozavr/api/v1/encode.cpp
        src/stegozavr/api/v1/decode.cpp
        third_party/in_image_hider/hider_png.cpp

)

find_package(PNG REQUIRED)
if (${PNG_FOUND})
    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(BACKEND ${PNG_LIBRARIES})
endif()



add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(BACKEND userver-core)
target_link_libraries(${PROJECT_NAME}  BACKEND)

#TESTING:
#add_subdirectory(tests)
