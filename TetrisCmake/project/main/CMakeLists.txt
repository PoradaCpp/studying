# CMakeLists.txt

file(GLOB_RECURSE exec_sources "src/*.h" "src/*.cpp")

include_directories("src" "${CMAKE_BINARY_DIR}/exports")
add_executable(tetris ${exec_sources})
target_link_libraries(tetris tetris_game)
