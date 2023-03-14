
set(TESTS_SOURCES engine_tests.cpp)

add_executable(EngineTests ${TESTS_SOURCES})
target_link_libraries(EngineTests BACKEND)
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})
target_link_libraries(EngineTests ${GTest_LIBRARIES})
if (${GTEST_FOUND})
    message("GTEST FOUND!")
    include_directories(${GTest_INCLUDE_DIRS})
    target_link_libraries(EngineTests ${GTest_LIBRARIES})
elseif()
    message("GTEST NOT FOUND!")
endif()

