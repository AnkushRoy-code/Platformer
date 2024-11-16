Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.0 # or a later release
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(Catch2)

add_executable(PlatformerTests
    window/test_window.cpp
)

target_include_directories(PlatformerTests PRIVATE ../Platformer)
target_link_libraries(PlatformerTests PRIVATE PlatformerLib Catch2::Catch2WithMain)

# Discover and register tests
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(PlatformerTests)
