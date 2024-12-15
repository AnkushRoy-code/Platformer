include(FetchContent)

# Find libraries
find_package(OpenGL REQUIRED)

set(FETCHCONTENT_QUIET FALSE)

# If you are wondering why I do not use the Git url method for FetchContent. It is because the repos are sometimes really big and can contain stuff we do not need, for example the Dear ImGui repo is of 200mb and the .git folder is of 170mb!

# SDL -- Please do not compile this, have a heart for you...
FetchContent_Declare(
    SDL2
    URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.10/SDL2-2.30.10.zip
    URL_HASH SHA256=14b06b30d3400953875e73b0c4771cad1483488a1ef816803610f22b32300ce8
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    FIND_PACKAGE_ARGS
)

# Glew Fetch (OpenGL ExtensionLoader)
FetchContent_Declare(
    GLEW
    URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
    URL_HASH SHA256=a9046a913774395a095edcc0b0ac2d81c3aacca61787b39839b941e9be14e0d4
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    FIND_PACKAGE_ARGS
)

# GLM (OpenGL Mathematics)
FetchContent_Declare(
	glm
    URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
    URL_HASH SHA256=9a995de4da09723bd33ef194e6b79818950e5a8f2e154792f02e4615277cfb8d
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    FIND_PACKAGE_ARGS
)

# Entt Fetch (ECS - Entity Component System)
FetchContent_Declare(
    EnTT
    URL https://github.com/skypjack/entt/archive/refs/tags/v3.14.0.zip
    URL_HASH SHA256=3c3d8014294bf1918e5e1aae537dc823f68964fa3c3dec99d10fa22e5d63a6fe
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# box2d Fetch (Physics)
FetchContent_Declare(
    box2d
    URL https://github.com/erincatto/box2d/archive/f0763aca7d4dfa8f1c19c2c4a9e66fa6e93ea32e.zip
    URL_HASH SHA256=87b5c2006ce45bf3621cba25db62595d44e9bb4d07bac0f35d06ec073dc75cf0
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(SDL2 GLEW glm EnTT box2d)

add_library(PlatformerLib
    Platformer/eventHandler.cpp
    Platformer/Platformer.cpp
    Platformer/window.cpp
    Platformer/OpenGL.cpp
    Platformer/Physics.cpp
    Platformer/keyState.cpp

    Platformer/Player/Player.cpp

    utils/Component.cpp
    utils/PhysicsMap.cpp
    # utils/GameObject.cpp
    utils/Map.cpp
    utils/TextureManager.cpp
    utils/Time.cpp
)

target_include_directories(PlatformerLib PUBLIC
    # Dependencies
    ${SDL2_INCLUDE_DIRS}

    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${glm_INCLUDE_DIRS}

    ${entt_SOURCE_DIR}
    ${Box2D_INCLUDE_DIRS}

    # My stuff
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(PlatformerLib PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    OpenGL::GL
    OpenGL::OpenGL
    OpenGL::GLU
    glm::glm
    GLEW
    EnTT
    box2d
)

add_executable(PlatformerExe main.cpp)
target_link_libraries(PlatformerExe PRIVATE PlatformerLib)
