project(feature_extraction_test)
cmake_minimum_required(VERSION 3.5)
find_package(OpenCV REQUIRED)
set(HDRS keypoint_processing_utils.h)
add_executable(${PROJECT_NAME} main.cpp ${HDRS})

set(RESOURCE_FILES
    resources/image_a.png
    resources/mt_image_1.JPG
    resources/mt_image_2.JPG
    resources/mt_image_3.JPG
    resources/mt_image_4.JPG
    resources/mt_image_5.JPG)


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
add_executable(test_keypoints_matching test_keypoints_matching.cpp)
target_compile_features(test_keypoints_matching PRIVATE cxx_std_17)
target_link_libraries(
  test_keypoints_matching
  gtest
  gmock
  gtest_main
  OpenCV
  ${CMAKE_THREAD_LIBS_INIT}
  PIPELINE_UTILS::Pipeline_utils
  PIPELINE::KEYPOINT_PROC_LIB
  PIPELINE::INTERFACES)
gtest_add_tests(TARGET test_keypoints_matching TEST_SUFFIX .noArgs TEST_LIST
                noArgsTests)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:feature_extraction_test>/resources/)

add_custom_command(TARGET test_keypoints_matching PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/resources/keypoint_matching $<TARGET_FILE_DIR:test_keypoints_matching>/resources/keypoint_matching)