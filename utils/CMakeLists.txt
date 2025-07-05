add_library(utils INTERFACE)

target_sources(utils INTERFACE BaseGUI.h BaseScreenController.h Point.h BoundaryBox.h helper_funcs.h BitVector.h)

target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(bmpManager bmpManager.cpp bmpManager.h)
target_include_directories(bmpManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bmpManager PRIVATE ePaper fonts GUI)