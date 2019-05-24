project(test1)

add_executable(test1 main.cpp)
target_link_libraries(test1 ${TARGET_NAME})
target_compile_features( test1 PUBLIC cxx_std_17 )

