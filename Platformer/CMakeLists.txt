include(FetchContent)

# Find libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Entt Fetch
FetchContent_Declare(
    EnTT
    URL https://github.com/skypjack/entt/archive/refs/tags/v3.14.0.zip
    URL_HASH SHA256=3c3d8014294bf1918e5e1aae537dc823f68964fa3c3dec99d10fa22e5d63a6fe
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(EnTT)

add_library(PlatformerLib
    Platformer/Platformer.cpp
    Platformer/GameObject.cpp
    window/window.cpp
    input/eventHandler.cpp
    utils/TextureManager.cpp
    utils/Map.cpp
)
target_include_directories(PlatformerLib PUBLIC
    ${entt_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Platformer
)

target_link_libraries(PlatformerLib PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    EnTT
)

add_executable(PlatformerExe main.cpp)
target_link_libraries(PlatformerExe PRIVATE PlatformerLib)
