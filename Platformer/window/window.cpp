#include "window.h"

#include <SDL.h>
#include <SDL_render.h>
#include <iostream>

namespace Platformer
{

bool Window::init(const std::string &title,
                  SDL_Window *&Window,
                  SDL_Renderer *&Renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                  << '\n';
        return false;
    }

    auto window_flags = SDL_WindowFlags(SDL_WINDOW_ALLOW_HIGHDPI
                                        | SDL_WINDOW_FULLSCREEN_DESKTOP);

    Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 0, 0, window_flags);

    if (Window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << '\n';
        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, 0);

    return true;
}

void Window::close(SDL_Window *&Window, SDL_Renderer *&Renderer)
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}
}  // namespace Platformer
