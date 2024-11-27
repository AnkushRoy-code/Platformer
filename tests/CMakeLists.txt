find_package(Catch2 REQUIRED)

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
