#include "Platformer/window.h"
#include "utils/constants.h"

#include <SDL.h>
#include <iomanip>
#include <string>
#include <iostream>

float maxF(float a, float b);
float minF(float a, float b);

namespace Platformer
{

SDL_Window *Window::window      = nullptr;
SDL_GLContext Window::glContext = nullptr;
double Window::WindowScale      = 0;

bool Window::init(const std::string &Title)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                  << '\n';
        return false;
    }

    WindowScale = getScaleFactor();

    auto window_flags =
        SDL_WindowFlags(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    // | SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        // Needs cleanup. Will do later.
        WindowScale * TILESET_WIDTH
            * TILESET_SIZE,  // The width is tiles * tilesize here 30 * 32
        WindowScale * TILESET_HEIGHT
            * TILESET_SIZE,  // Same as width but 18 * 32
        window_flags);

    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError()
                  << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Window::close()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// https://github.com/indianakernick/EnTT-Pacman/blob/master/src/core/app.cpp#L22
float Window::getScaleFactor()
{
    SDL_Rect bounds {};

    // Make the largest window possible with an integer scale factor
#if SDL_VERSION_ATLEAST(2, 0, 5)
    SDL_GetDisplayUsableBounds(0, &bounds);
#else
#    warning SDL 2.0.5 or later is recommended
    SDL_GetDisplayBounds(0, &bounds);
#endif

    const float scaleX = float(bounds.w) / float(TILESET_WIDTH * TILESET_SIZE);
    const float scaleY = float(bounds.h) / float(TILESET_HEIGHT * TILESET_SIZE);

    return maxF(1, minF(scaleX, scaleY));
}

}  // namespace Platformer

float maxF(float a, float b)
{
    return a > b ? a : b;
}
float minF(float a, float b)
{
    return a < b ? a : b;
}
