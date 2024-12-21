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
)

target_include_directories(Core PUBLIC     
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
    ${entt_SOURCE_DIR}/src
)

target_link_libraries(Core PUBLIC 
    SDL2::SDL2
    OpenGL::GL
    OpenGL::GLU
    glm::glm
    Utils
    Player
    Debug
    libglew_shared
)
