project(feature_extraction)
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-Wall -Wextra -pedantic)

find_package(OpenCV HINTS "${OPENCV_DIR}" REQUIRED)
find_package(gflags REQUIRED)
# Only link with required opencv modules.
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_xfeatures2d opencv_features2d opencv_calib3d opencv_highgui )
# Add source directory

#include_directories(utils ${PROJECT_SOURCE_DIR}/../../utils/src)
#include_directories(${OPENCV_DIR})
#aux_source_directory("./src" SRC_LIST)
#aux_source_directory("../../utils/src" SRC_LIST_2)

# Add executable
add_executable(${PROJECT_NAME} ./src/main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} gflags)

#adding testing directory
enable_testing()
add_subdirectory(tests)