project(Pipeline_utils)
cmake_minimum_required(VERSION 3.5.1)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)
file(GLOB SRCS
          ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/active/*.cpp
  )

add_library(${PROJECT_NAME} ${SRCS})
add_library(PIPELINE_UTILS::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
include_directories(Pipeline_interfaces/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} gflags
                      OpenCV
                      Pipeline_interfaces
                      )

target_include_directories(${PROJECT_NAME}
    PUBLIC
       $<INSTALL_INTERFACE:include>
       $<INSTALL_INTERFACE:include/active>

       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/active>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        
)
#---------------------------------------------------------------------------------
#export target

set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME PIPELINE_UTILS_LIB)
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
    PIPELINE_UTILS::
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


export(EXPORT ${PROJECT_NAME}-target 
	   FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-target.cmake 
	   NAMESPACE PIPELINE_UTILS::)

#Register package in user's package registry
export(PACKAGE PIPELINE_UTILS)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
enable_testing()
add_subdirectory(test)
#-----------------------------------------------------------------------------------