# Task Table Ui CMakeLists.txt

file(GLOB_RECURSE exec_sources "src/*.h" "src/*.cpp")
file(GLOB_RECURSE exec_includes "include/*.h")
file(GLOB_RECURSE exec_forms "forms/*.ui")

set(CMAKE_AUTOUIC_SEARCH_PATHS "forms")

include_directories("src" "include" "forms" "${CMAKE_BINARY_DIR}/exports")
add_executable(task_table ${exec_sources} ${exec_includes} ${exec_forms})
target_link_libraries(task_table datamodel)
