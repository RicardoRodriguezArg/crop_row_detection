project(photogrametric_utils_tests)
cmake_minimum_required(VERSION 3.1)
include (../cmake/GMockConfig.cmake)
find_package(GTest REQUIRED)
find_package( Threads REQUIRED)

add_executable(${PROJECT_NAME} tests_utils_photogrametric_pipeline.cpp)
message(STATUS "Pipeline Include dir : PIPELINE_UTILS::Pipeline_utils")

#
target_link_libraries(${PROJECT_NAME}
#    
    
    gtest gmock gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
    PIPELINE_UTILS::Pipeline_utils
)
gtest_add_tests(TARGET      ${PROJECT_NAME}
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

 set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)