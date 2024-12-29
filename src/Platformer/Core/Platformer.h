#ifndef INCLUDE_PLATFORMER_PLATFORMER_H_
#define INCLUDE_PLATFORMER_PLATFORMER_H_

#include "Platformer/Core/Music.h"
#include "Platformer/Player/Player.h"
#include "box2d/id.h"
#include "Utils/Map.h"

#include <SDL.h>
#include <memory>

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
    void handleInput(const b2BodyId &bodyId);

private:
    std::unique_ptr<Player> mPlayer = std::make_unique<Player>();
    ma_sound bgSound;

    bool mIsRunning {};
    Map mMap {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_PLATFORMER_H_
