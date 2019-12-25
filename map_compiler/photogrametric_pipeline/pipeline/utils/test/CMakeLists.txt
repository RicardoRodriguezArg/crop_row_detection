project(photogrametric_utils_tests)
cmake_minimum_required(VERSION 3.1)



add_executable(${PROJECT_NAME} tests_utils_photogrametric_pipeline.cpp)


target_link_libraries(${PROJECT_NAME}
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