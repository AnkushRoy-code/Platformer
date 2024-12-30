add_library(Components
    Component.cpp
    Component.h
    Animation.cpp
    Animation.h
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
    ${glew_SOURCE_DIR}/include
)
