project(feature_extraction_test)
cmake_minimum_required(VERSION 3.5)

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(${PROJECT_NAME}
    gtest gmock gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
    PIPELINE::KEYPOINT_PROC_LIB
)
gtest_add_tests(TARGET      ${PROJECT_NAME}
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

 set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)




#TODO: Fix include directories 
#add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )