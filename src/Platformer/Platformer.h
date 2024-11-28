///
/// Includes the Game Class
///

#ifndef INCLUDE_PLATFORMER_PLATFORMER_H_
#define INCLUDE_PLATFORMER_PLATFORMER_H_

#include "utils/TextureManager.h"
#include <SDL.h>
#include <SDL_video.h>

namespace Platformer
{

class Game
{
public:
    /**
     * Runs The whole damn thing.
     *
     * @return void
     */
    void run();

private:
    void init();
    void handleEvents();
    void update();
    void render();
    void cleanup();

private:
    bool mIsRunning {};
    SDL_Window *mWindow {};
    SDL_GLContext mContext {};
    GLuint mShaderProgramme {};
    GLuint mVAO {}, mVBO{}, mEBO{};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_PLATFORMER_H_
