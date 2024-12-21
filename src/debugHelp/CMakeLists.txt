add_library(Debug
    box2dDebugDraw.cpp
    box2dDebugDraw.h
)

target_include_directories(Debug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Debug PUBLIC box2d)
