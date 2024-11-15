#include "window.h"
#include "Platformer/Platformer.h"

#include <SDL.h>
#include <SDL_render.h>
#include <iostream>

namespace Platformer
{

bool Window::init(const std::string &title,
                  SDL_Window *&Window)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                  << '\n';
        return false;
    }

    auto window_flags = SDL_WindowFlags(SDL_WINDOW_ALLOW_HIGHDPI);
                                        // | SDL_WINDOW_FULLSCREEN_DESKTOP);

    Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 800, 640, window_flags);

    if (Window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << '\n';
        return false;
    }

    Game::mRenderer = SDL_CreateRenderer(Window, -1, 0);

    return true;
}

void Window::close(SDL_Window *&Window)
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Game::mRenderer);
    SDL_Quit();
}
}  // namespace Platformer
