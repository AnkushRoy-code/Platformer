add_library(Utils
    PhysicsMap.cpp
    PhysicsMap.h
    BackGround.cpp
    BackGround.h
    Map.cpp
    Map.h
    TextureManager.cpp
    TextureManager.h
    Time.cpp
    Time.h
)

add_subdirectory(Components)

target_include_directories(Utils PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(Utils PUBLIC box2d Components)
