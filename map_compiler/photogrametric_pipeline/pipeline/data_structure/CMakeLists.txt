project( data_structure )
cmake_minimum_required(VERSION 3.5.1)

# Only link with required opencv modules. Add source directory
set(SRCS ${PROJECT_NAME}_SRCS)
file(GLOB SRCS "./src/*.cpp")

add_library(${PROJECT_NAME} ${SRCS})
add_library(PIPELINE::DATA_STRUCTURE ALIAS ${PROJECT_NAME})

# Link
target_link_libraries(
  ${PROJECT_NAME} PRIVATE PIPELINE_UTILS::Pipeline_utils PIPELINE::INTERFACES
                          ${OpenCV_LIBS} glog::glog)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<INSTALL_INTERFACE:include/camera>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/camera>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/camera
          ${CMAKE_CURRENT_SOURCE_DIR}/src/camera
                          )
set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME DATA_STRUCTURE_LIB)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-target
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  EXPORT ${PROJECT_NAME}-target
  FILE ${PROJECT_NAME}-target.cmake
  NAMESPACE PIPELINE::
  DESTINATION ${INSTALL_CONFIGDIR})

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake INSTALL_DESTINATION
  ${INSTALL_CONFIGDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR})
# Exporting from the build tree

export(
  EXPORT ${PROJECT_NAME}-target
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-target.cmake
  NAMESPACE PIPELINE::
       )

export(PACKAGE DATA_STRUCTURE_LIB)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# adding testing directory
enable_testing()
#add_subdirectory(test)
