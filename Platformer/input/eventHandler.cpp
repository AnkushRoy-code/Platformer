#include "eventHandler.h"
#include <SDL_events.h>

namespace Platformer
{
void Input::handleInputs(bool &isRunning)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }
}

}  // namespace Platformer
