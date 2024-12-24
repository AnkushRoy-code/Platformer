# Made a different directory thinking I will have a lot of components. As of now I only have 2 because I calculated wrong. :(


add_library(Components
    Component.cpp
    Component.h
)

target_include_directories(Components PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
    ${SDL2_INCLUDE_DIRS}
)
