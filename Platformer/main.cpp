#include "Platformer/Platformer.h"
#include "SDL_timer.h"
#include <cstdint>

int main()
{
    Platformer::Game Platformer;
    Platformer.init();

    // For FPS capping
    const std::uint8_t FPS = 60;
    const int frameDelay   = 1000 / FPS;
    std::uint32_t frameStart {};
    int frameTime {};

    while (Platformer.isRunning())
    {
        frameStart = SDL_GetTicks();

        Platformer.handleEvents();
        Platformer.update();
        Platformer.render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    Platformer.clean();

    return 0;
}
