project(Pipeline_process)
cmake_minimum_required(VERSION 3.5.1)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
add_definitions(-Wall -Wextra -pedantic)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#finding external libraries and turning as imported target
include (cmake/GMockConfig.cmake)
find_package(GTest REQUIRED)

add_library(GTest INTERFACE IMPORTED)
set_property(TARGET GTest PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})

find_package(Threads REQUIRED)    
add_library(Threads INTERFACE IMPORTED)

find_package(OpenCV REQUIRED)
add_library(OpenCV INTERFACE IMPORTED)
set_property(TARGET OpenCV PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${OpenCV_INCLUDE_DIRS})

find_package(gflags REQUIRED)
#add_library(gflags INTERFACE IMPORTED)

find_package(glog REQUIRED)
add_library(glog INTERFACE IMPORTED)

enable_testing()

add_subdirectory(utils)
add_subdirectory(interfaces)
add_subdirectory(keypoints_processor)
add_subdirectory(processor)