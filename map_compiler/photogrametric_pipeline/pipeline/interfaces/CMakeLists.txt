project(Pipeline_interfaces)
cmake_minimum_required(VERSION 3.5.1)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

add_definitions(-Wall -Wextra -pedantic)
add_library(${PROJECT_NAME} INTERFACE)
add_library(PIPELINE::INTERFACES ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

)
#---------------------------------------------------------------------------------
#export target

set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME PIPELINE_INTERFACES)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-target
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT ${PROJECT_NAME}-target
  FILE
    ${PROJECT_NAME}-target.cmake
  NAMESPACE
    PIPELINE_INTERFACES::
  DESTINATION
  	${INSTALL_CONFIGDIR}
    
)
configure_package_config_file(
	${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

## Exporting from the build tree


export(
     EXPORT ${PROJECT_NAME}-target 
	   FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-target.cmake 
	   NAMESPACE PIPELINE_INTERFACES::
     )

#Register package in user's package registry
export(PACKAGE PIPELINE_INTERFACES)


