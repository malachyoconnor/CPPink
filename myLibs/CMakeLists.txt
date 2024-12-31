add_library(myBmpManager
        myBmpManager.cpp
        myBmpManager.h
)

target_include_directories(myBmpManager
        PUBLIC  # <-- IMPORTANT: Let consumers see your include path
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(myBmpManager
        PUBLIC
        config
        ePaper
        fonts
        GUI
)

add_library(myGUI INTERFACE)  # header-only library

target_sources(myGUI
        INTERFACE
        myGUI.h
)

target_include_directories(myGUI
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# IMPORTANT: link the non-header-only library here so that
# myGUI will inherit all usage requirements from myBmpManager
target_link_libraries(myGUI
        INTERFACE
        myBmpManager
)
