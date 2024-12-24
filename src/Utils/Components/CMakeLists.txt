add_library(Components
    Component.cpp
    Component.h
    TileComponent.cpp
    TileComponent.h
)

target_include_directories(Components PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
    ${SDL2_INCLUDE_DIRS}
)
