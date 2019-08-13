# rand_num_gen_lib, CMakeLists.txt

file(GLOB_RECURSE lib_includes "include/*.h")
file(GLOB_RECURSE lib_sources "src/*.h" "src/*.cpp")

include_directories("include" "src" "${CMAKE_BINARY_DIR}/exports")
add_library(rand_num_gen STATIC ${lib_includes} ${lib_sources})

target_include_directories(rand_num_gen PUBLIC "include")

