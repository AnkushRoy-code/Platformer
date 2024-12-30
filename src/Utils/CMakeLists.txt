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

if(isStatic)
    target_include_directories(Utils PUBLIC 
        ${sdl2_SOURCE_DIR}/include
    )
else()
    target_include_directories(Utils PUBLIC 
        ${SDL2_INCLUDE_DIRS}
    )
endif()

target_include_directories(Utils PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
    ${glew_SOURCE_DIR}/include
)

target_link_libraries(Utils PUBLIC box2d Components)
