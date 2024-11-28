#include "Platformer/window.h"

#include <SDL.h>
#include <SDL_mutex.h>
#include <SDL_video.h>
#include <iostream>

float max(float a, float b)
{
    return a > b ? a : b;
}
float min(float a, float b)
{
    return a < b ? a : b;
}
namespace Platformer
{

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

    const float scaleX = float(bounds.w) / float(30 * 32);
    const float scaleY = float(bounds.h) / float(18 * 32);

    std::cout << "scaleFactor: " << max(1, min(scaleX, scaleY)) << std::endl;

    return max(1, min(scaleX, scaleY));
}

bool Window::init(const std::string &Title,
                  SDL_Window *&Window,
                  SDL_GLContext &Context)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                  << '\n';
        return false;
    }

    float scaleFactor = getScaleFactor();
    scaleFactor       = 1;  // For now, getScaleFactor() needs work.

    auto window_flags =
        SDL_WindowFlags(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    // | SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    Window = SDL_CreateWindow(
        Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        // Needs cleanup. Will do later.
        scaleFactor * 30 * 32,  // The width is tiles * tilesize here 30 * 32
        scaleFactor * 18 * 32,  // Same as width but 18 * 32
        window_flags);

    if (Window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }
    std::cout << "SDL_Window initialised successfully!\n";

    Context = SDL_GL_CreateContext(Window);
    if (!Context)
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError()
                  << std::endl;
        SDL_DestroyWindow(Window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Window::close(SDL_Window *&Window, SDL_GLContext &Context)
{
    SDL_GL_DeleteContext(Context);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
}  // namespace Platformer
