add_library(utils INTERFACE)

target_sources(utils INTERFACE BaseGUI.h BaseScreenController.h Point.h BoundaryBox.h helper_funcs.h bmpManager.h)

target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
