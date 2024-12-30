add_library(fonts STATIC fonts.h font8.c font12.c font12CN.c font16.c font20.c font24.c font24CN.c)

target_include_directories(fonts
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
