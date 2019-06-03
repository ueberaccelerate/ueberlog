project ( tools )
message ( STATUS "Enabled build with tools ")

set ( NANOGUI_BUILD_EXAMPLE OFF )
set ( NANOGUI_BUILD_PYTHON  OFF )

if ( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/nanogui/ )
  add_subdirectory( nanogui )
else()
  message ( FATAL_ERROR "checkout git project https://github.com/wjakob/nanogui.git and do git submodule --init --recursive " )
endif()
add_subdirectory( logger_viewer )

target_include_directories ( logger_viewer PUBLIC nanogui/include nanogui/ext/eigen)
target_include_directories ( logger_viewer PUBLIC nanogui/include nanogui/ext/glfw/include)
target_include_directories ( logger_viewer PUBLIC nanogui/include nanogui/ext/nanovg/src)
