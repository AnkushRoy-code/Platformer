add_library(Utils
    Component.cpp
    Component.h
    PhysicsMap.cpp
    PhysicsMap.h
    Map.cpp
    Map.h
    TextureManager.cpp
    TextureManager.h
    Time.cpp
    Time.h
)

target_include_directories(Utils PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(Utils PUBLIC box2d)
