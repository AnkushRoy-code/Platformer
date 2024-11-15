///
/// Includes the Game Class
///

#ifndef INCLUDE_PLATFORMER_PLATFORMER_H_
#define INCLUDE_PLATFORMER_PLATFORMER_H_

#include <SDL.h>

namespace Platformer
{

class Game
{
public:
    void init();
    void handleEvents();
    void update();
    void render();
    void clean();

    [[nodiscard]] bool isRunning() const
    {
        return mIsRunning;
    }

    static SDL_Renderer *mRenderer;
private:
    bool mIsRunning {};
    SDL_Window *mWindow {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_PLATFORMER_H_
