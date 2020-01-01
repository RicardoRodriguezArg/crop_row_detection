project(photogrametric_utils_tests)
cmake_minimum_required(VERSION 3.1)

set(RESOURCE_FILES
  				resources/image_a.png

)
set(CMAKE_CXX_STANDARD 14)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FILES}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_executable(${PROJECT_NAME} tests_utils_photogrametric_pipeline.cpp)


target_link_libraries(${PROJECT_NAME}
    gtest gmock gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
    PIPELINE_UTILS::Pipeline_utils
    ${OpenCV_LIBS}
	OpenCV
	
)
gtest_add_tests(TARGET      ${PROJECT_NAME}
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

 set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)