project(motion_recovery)
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-Wall -Wextra -pedantic)

find_package(OpenCV HINTS "${OPENCV_DIR}" REQUIRED)
find_package(gflags REQUIRED)
# Only link with required opencv modules.
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_xfeatures2d opencv_features2d)
# Add source directory
include_directories(./src)
include_directories(${OPENCV_DIR})
aux_source_directory("./src" SRC_LIST)

# Add exectuteable
add_executable(${PROJECT_NAME} ${SRC_LIST})
# Link
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} gflags)

#adding testing directory
enable_testing()
add_subdirectory(tests)
