# Made a different directory thinking I will have a lot of components. As of now I only have 2 because I calculated wrong. :(


add_library(Components
    Component.cpp
    Component.h
)

if(isStatic)
    target_include_directories(Components PUBLIC 
        ${sdl2_SOURCE_DIR}/include
    )
else()
    target_include_directories(Components PUBLIC 
        ${SDL2_INCLUDE_DIRS}
    )
endif()

target_include_directories(Components PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)
