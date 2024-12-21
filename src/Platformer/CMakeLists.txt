add_subdirectory(Core)
add_subdirectory(Player)
add_subdirectory(Physics)

add_library(PlatformerLib INTERFACE)
target_link_libraries(PlatformerLib INTERFACE Core Player Physics Utils)
