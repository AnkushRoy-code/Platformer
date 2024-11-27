include(FetchContent)

# Find libraries
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# Entt Fetch
FetchContent_Declare(
    EnTT
    URL https://github.com/skypjack/entt/archive/refs/tags/v3.14.0.zip
    URL_HASH SHA256=3c3d8014294bf1918e5e1aae537dc823f68964fa3c3dec99d10fa22e5d63a6fe
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(
    GLEW
    URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
    URL_HASH SHA256=a9046a913774395a095edcc0b0ac2d81c3aacca61787b39839b941e9be14e0d4
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(GLEW)

add_library(PlatformerLib
    Platformer/eventHandler.cpp
    Platformer/Platformer.cpp
    Platformer/window.cpp
    Platformer/OpenGL.cpp

    utils/Component.cpp
    # utils/GameObject.cpp
    utils/Map.cpp
    utils/TextureManager.cpp
    utils/Time.cpp
)
target_include_directories(PlatformerLib PUBLIC
    ${entt_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    # ${SDL2_IMAGE_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(PlatformerLib PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    OpenGL::GL
    OpenGL::OpenGL
    OpenGL::GLU
    GLEW
    EnTT
)

add_executable(PlatformerExe main.cpp)
target_link_libraries(PlatformerExe PRIVATE PlatformerLib)
