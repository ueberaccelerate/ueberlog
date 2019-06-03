project ( logger_viewer )


add_executable ( logger_viewer logger_viewer_main.cpp )


target_compile_features( logger_viewer PUBLIC cxx_std_17 )
target_link_libraries ( logger_viewer PUBLIC nanogui )
target_include_directories ( logger_viewer PUBLIC nanogui/include nanogui/ext/eigen)
target_include_directories ( logger_viewer PUBLIC nanogui/include nanogui/ext/glfw/include)
target_include_directories ( logger_viewer PUBLIC nanogui/include nanogui/ext/nanovg/src)

