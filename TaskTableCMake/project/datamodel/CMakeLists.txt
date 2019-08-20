# tasks_table_datamodel, CMakeLists.txt

include(GenerateExportHeader)

file(GLOB_RECURSE lib_includes "include/*.h")
file(GLOB_RECURSE lib_sources "src/*.h" "src/*.cpp")

include_directories("include" "src" "${CMAKE_BINARY_DIR}/exports")
add_library(datamodel SHARED ${lib_includes} ${lib_sources})
generate_export_header(datamodel EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/exports/datamodel_export.h")

target_link_libraries(datamodel Qt5::Widgets)
target_include_directories(datamodel PUBLIC "include")

