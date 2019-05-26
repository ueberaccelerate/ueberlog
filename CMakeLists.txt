cmake_minimum_required( VERSION 3.4.3 )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
project( ueberlog )

#include(common)
#info( "Module path: ${CMAKE_MODULE_PATH}" )

set (TARGET_NAME ${PROJECT_NAME})

#info( "Target name: ${TARGET_NAME}" )
add_library(${TARGET_NAME} SHARED "")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(example)

target_compile_features( ${TARGET_NAME} PUBLIC cxx_std_17 )
target_include_directories ( ${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
