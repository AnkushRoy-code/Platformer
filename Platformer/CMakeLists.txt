add_library(PlatformerGame
    Platformer/Platformer.cpp
    Platformer/GameObject.cpp
)

add_library(PlatformerWindow
    window/window.cpp
)

add_library(PlatformerInput
    input/eventHandler.cpp
)

add_library(PlatformerUtils
    utils/TextureManager.cpp
)

target_include_directories(PlatformerGame PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/Platformer)
target_include_directories(PlatformerWindow PUBLIC ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/Platformer/window)

target_link_libraries(PlatformerGame PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
target_link_libraries(PlatformerUtils PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
target_link_libraries(PlatformerWindow PRIVATE SDL2::SDL2)
target_link_libraries(PlatformerInput PRIVATE SDL2::SDL2)

add_executable(PlatformerExe main.cpp)

target_link_libraries(PlatformerExe PRIVATE PlatformerGame PlatformerWindow PlatformerInput PlatformerUtils)
