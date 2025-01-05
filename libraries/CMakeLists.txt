add_library(myGUI myGUI.h myGUI.cpp)
target_include_directories(myGUI PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/utils)
target_link_libraries(myGUI PUBLIC config ePaper fonts GUI examples myBmpManager utils)

add_library(myBmpManager myBmpManager.cpp myBmpManager.h)
target_include_directories(myBmpManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(myBmpManager PRIVATE ePaper fonts GUI)