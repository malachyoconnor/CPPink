add_library(myBmpManager myBmpManager.cpp myBmpManager.h)
target_include_directories(myBmpManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(myBmpManager PRIVATE config ePaper fonts GUI myGUI)


add_library(myGUI myGUI.h myGui.cpp)
target_include_directories(myGUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(myGUI PRIVATE config ePaper fonts GUI myBmpManager)
