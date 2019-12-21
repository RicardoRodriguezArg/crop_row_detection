project(odm_georef)
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)
# Set pcl dir to the input spedified with option -DPCL_DIR="path"
set(PCL_DIR "PCL_DIR-NOTFOUND" CACHE "PCL_DIR" "Path to the pcl installation directory")
set(OPENCV_DIR "OPENCV_DIR-NOTFOUND" CACHE "OPENCV_DIR" "Path to the opencv installation directory")

#find_library(PROJ4_LIBRARY "libproj.so" PATHS "/usr/lib" "/usr/lib/x86_64-linux-gnu")
find_package(jsoncpp REQUIRED)
#set(PROJ4_LIBRARY "/usr/lib/x86_64-linux-gnu/libproj.so" CACHE "PROJ4_LIBRARY" "Path to the proj4 library directory")

# Add compiler options.
add_definitions(-Wall -Wextra -Wconversion -pedantic -std=c++11)

# Find pcl at the location specified by PCL_DIR
find_package(VTK REQUIRED)
find_package(PCL 1.8 HINTS "${PCL_DIR}/share/pcl-1.8")

# Find OpenCV at the default location
find_package(OpenCV HINTS "${OPENCV_DIR}" REQUIRED)

# Only link with required opencv modules.
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# Add the PCL and Eigen include dirs. 
# Necessary since the PCL_INCLUDE_DIR variable set bu find_package is broken.)
include_directories(${PCL_ROOT}/include/pcl-${PCL_VERSION_MAJOR}.${PCL_VERSION_MINOR})
include_directories(${EIGEN_ROOT})

# PDAL and jsoncpp
find_package(PDAL REQUIRED CONFIG)
include_directories(${PDAL_INCLUDE_DIRS})

link_directories(${PDAL_LIBRARY_DIRS})
add_definitions(${PDAL_DEFINITIONS})
FIND_PACKAGE( Boost COMPONENTS filesystem system program_options REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
# Add source directory
aux_source_directory("./src" SRC_LIST)

# Add exectuteable
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Link
target_link_libraries(${PROJECT_NAME} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_SURFACE_LIBRARIES} ${OpenCV_LIBS} ${JSONCPP_LIBRARIES} ${PDAL_LIBRARIES}
 ${Boost_LIBRARIES}
 )
