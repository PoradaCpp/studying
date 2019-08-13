# tetris_game_lib, CMakeLists.txt

include(GenerateExportHeader)

file(GLOB_RECURSE lib_includes "include/*.h")
file(GLOB_RECURSE lib_sources "src/*.h" "src/*.cpp")

include_directories("include" "src" "${CMAKE_BINARY_DIR}/exports")
add_library(tetris_game SHARED ${lib_includes} ${lib_sources})
generate_export_header(tetris_game EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/exports/tetris_game_export.h")

target_link_libraries(tetris_game tetris_obj rand_num_gen)
target_include_directories(tetris_game PUBLIC "include")

