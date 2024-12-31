#include "Platformer/Core/EventHandler.h"

#include <SDL.h>
#include <functional>

#include "Platformer/Core/KeyState.h"

namespace Platformer
{

void Input::handleInputs(bool &isRunning)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
                // clang-format off
            case SDL_QUIT            : isRunning = false; break;
            case SDL_MOUSEBUTTONDOWN : changeCursorState(KeyState::keyPress, event); break;
            case SDL_MOUSEBUTTONUP   : changeCursorState(KeyState::keyRelease, event); break;
            case SDL_KEYDOWN         : changeKeyState(KeyState::keyPress, event); break;
            case SDL_KEYUP           : changeKeyState(KeyState::keyRelease, event); break;
            default                  : break;
                // clang-format on
        }
    }
}

void Input::changeKeyState(const std::function<void(int)> &function,
                           const SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
            // clang-format off
        case SDLK_a      :
        case SDLK_LEFT   : function(KeyState::LEFT); break;
        case SDLK_d      :
        case SDLK_RIGHT  : function(KeyState::RIGHT); break;
        case SDLK_SPACE  : function(KeyState::SPACE); break;
        case SDLK_LSHIFT :
        case SDLK_RSHIFT : function(KeyState::SHIFT); break;
        default          : break;
            // clang-format on
    }
}

void Input::changeCursorState(const std::function<void(int)> &function,
                              const SDL_Event &event)
{
    switch (event.button.button)
    {
            // clang-format off
        case SDL_BUTTON_RIGHT  : function(KeyState::R_MOUSEBUTTON); break;
        case SDL_BUTTON_LEFT   : function(KeyState::L_MOUSEBUTTON); break;
        case SDL_BUTTON_MIDDLE : function(KeyState::M_MOUSEBUTTON); break;
        default                : break;
            // clang-format on
    }
}

}  // namespace Platformer
