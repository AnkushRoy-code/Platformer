#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <SDL.h>
#include <string>
#include "Platformer/window.h"

using namespace Platformer;

TEST_CASE("Platformer::Window - Initialization and Cleanup", "[Window]") {
    // SDL_Window *window = nullptr;
    // const std::string title = "Test Window";

    // SECTION("Initialization") {
    //     REQUIRE(Window::init(title, window)); // Ensure the window is successfully initialized
    //     REQUIRE(window != nullptr);          // Window pointer should not be null after init
    //     REQUIRE(SDL_GetWindowTitle(window) == title); // Title should match the one provided
    // }

    // SECTION("Cleanup") {
    //     REQUIRE_NOTHROW(Window::close(window)); // Ensure close does not throw any exceptions
    //     REQUIRE(window == nullptr);            // Window pointer should be null after close
    // }
}
