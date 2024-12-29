add_library(Core
    Platformer.cpp
    Platformer.h
    Window.cpp
    Window.h
    EventHandler.cpp
    EventHandler.h
    KeyState.cpp
    KeyState.h
    OpenGL.cpp
    OpenGL.h
    Music.cpp
    Music.h
)

target_include_directories(Core PUBLIC     
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)

if(isStatic)
    target_link_libraries(Core PUBLIC 
        SDL2::SDL2-static
        libglew_static
    )
else()
    target_link_libraries(Core PUBLIC 
        SDL2::SDL2
        libglew_shared
    )
endif()

target_link_libraries(Core PUBLIC 
    OpenGL::GL
    OpenGL::GLU
    glm::glm
    Utils
    Player
    Debug
)
