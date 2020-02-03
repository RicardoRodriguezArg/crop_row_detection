project(motion_recovery_tests)
cmake_minimum_required(VERSION 3.5)
find_package(OpenCV REQUIRED)
set(HDRS)
add_executable(${PROJECT_NAME} main.cpp ${HDRS})

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
  PIPELINE::INTERFACES
  PIPELINE::MOTION_RECOVERY_LIB)

gtest_add_tests(TARGET ${PROJECT_NAME} TEST_SUFFIX .noArgs TEST_LIST
                noArgsTests)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)

add_custom_command(
  TARGET ${PROJECT_NAME}
  PRE_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/
    $<TARGET_FILE_DIR:motion_recovery_tests>/resources/)
