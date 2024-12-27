add_executable(PlatformerExe main.cpp)

if(isStatic)
    target_link_options(PlatformerExe PRIVATE -static-libgcc -static-libstdc++)
endif()

target_link_libraries(PlatformerExe PRIVATE PlatformerLib Utils)
