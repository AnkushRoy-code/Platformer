add_executable(PlatformerExe main.cpp)

if(isStatic)
    if (APPLE)
        message(WARNING "Wow you rich boi huh")
    else()
        target_link_options(PlatformerExe PRIVATE -static-libgcc -static-libstdc++)
    endif()
endif()

target_link_libraries(PlatformerExe PRIVATE PlatformerLib Utils)
