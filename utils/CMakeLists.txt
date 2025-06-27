add_library(utils INTERFACE)

target_sources(utils INTERFACE point.h bounding_box.h helper_funcs.h)

target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
