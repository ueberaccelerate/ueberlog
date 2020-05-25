cmake_minimum_required( VERSION 3.12 )
project( ueberlog )
set (TARGET_NAME ${PROJECT_NAME})

option(BUILD_THREAD_SAFE "Build with thread safety" ON)
option(BUILD_EXAMPLES    "Build with examples"      OFF)
option(BUILD_TOOLS       "Build with tools"         OFF)

option( BUILD_SHARED_LIBS "The shared library is made" OFF )

include ( cmake/warnings.cmake )

add_library(${TARGET_NAME}-cppfeatures INTERFACE )
add_library(${TARGET_NAME}-cppwarnings INTERFACE )

target_compile_features( ${TARGET_NAME}-cppfeatures INTERFACE cxx_std_17 )
target_include_directories( ${TARGET_NAME}-cppfeatures INTERFACE include )

set_project_warinigs( ${TARGET_NAME}-cppwarnings )


add_library(${TARGET_NAME})

add_subdirectory( include )
add_subdirectory( src     )

if ( ${BUILD_EXAMPLES} )
  add_subdirectory( example )
endif()

if ( ${BUILD_TOOLS} )
  add_subdirectory( tools   )
endif()

if (${BUILD_THREAD_SAFE})
  target_compile_definitions( ${TARGET_NAME} PRIVATE -DTHREAD_SAFE )
endif()

target_link_libraries( ${TARGET_NAME} PRIVATE ${TARGET_NAME}-cppfeatures ${TARGET_NAME}-cppwarnings )
