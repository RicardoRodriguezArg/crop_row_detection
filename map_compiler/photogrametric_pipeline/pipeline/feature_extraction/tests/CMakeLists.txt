project(feature_extraction_test)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)
find_package (Threads)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../scr)

#TODO: Fix include directories 
#add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )