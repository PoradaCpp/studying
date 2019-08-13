# tetris_obj_lib, CMakeLists.txt

file(GLOB_RECURSE lib_includes "include/*.h")
file(GLOB_RECURSE lib_sources "src/*.h" "src/*.cpp")

include_directories("include" "src" "${CMAKE_BINARY_DIR}/exports")
add_library(tetris_obj STATIC ${lib_includes} ${lib_sources})

target_include_directories(tetris_obj PUBLIC "include")

