add_library(Player
    Player.cpp
    Player.h
    PlayerState.cpp
    PlayerState.h
)

target_include_directories(Player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Player PUBLIC Core)
