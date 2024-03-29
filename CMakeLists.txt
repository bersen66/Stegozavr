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
include_directories(third_party/in_image_hider/include)
include_directories(third_party/png++/include)

find_package(Boost REQUIRED)
if (${Boost_FOUND})
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(
        BACKEND OBJECT
        src/stegozavr/api/v1/handlers/encode.cpp
        src/stegozavr/api/v1/handlers/decode.cpp
        src/stegozavr/api/v1/handlers/register_user.cpp
        src/stegozavr/api/v1/handlers/get_token.cpp
        src/stegozavr/api/v1/handlers/impl/db_utils.cpp
        src/stegozavr/engine/decode/decode.cpp
        src/stegozavr/engine/encode/encode.cpp
        third_party/in_image_hider/src/hider_png.cpp
)


find_package(PNG REQUIRED)
if (${PNG_FOUND})
    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(BACKEND ${PNG_LIBRARIES})
endif()


add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(BACKEND userver-core userver-postgresql userver-universal)
target_link_libraries(${PROJECT_NAME}  BACKEND)

#TESTING:
option(STEGOZAVR_ENABLE_UNIT_TESTS "Compile unit tests" OFF)
if (STEGOZAVR_ENABLE_UNIT_TESTS)
    add_subdirectory(tests/unit)
endif()

