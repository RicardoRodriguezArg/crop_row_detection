project(feature_extraction_test)
cmake_minimum_required(VERSION 3.5)
find_package(OpenCV REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)

set(RESOURCE_FILES resources/image_a.png resources/chess_board_test.gif)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FILES}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(
  ${PROJECT_NAME}
  gtest
  gmock
  gtest_main
  OpenCV
  ${CMAKE_THREAD_LIBS_INIT}
  PIPELINE_UTILS::Pipeline_utils
  PIPELINE::KEYPOINT_PROC_LIB
  PIPELINE::INTERFACES)
gtest_add_tests(TARGET ${PROJECT_NAME} TEST_SUFFIX .noArgs TEST_LIST
                noArgsTests)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)

# TODO: Fix include directories add_executable(${PROJECT_NAME} main.cpp)
# target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES}
# ${CMAKE_THREAD_LIBS_INIT} )
