#ifndef INCLUDE_PLATFORMER_PLATFORMER_H_
#define INCLUDE_PLATFORMER_PLATFORMER_H_

#include "Platformer/Player/Player.h"
#include "box2d/id.h"
#include "entt/entity/fwd.hpp"
#include "Utils/Map.h"

#include <SDL.h>

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

    static entt::registry Registry;
    static entt::entity PlayerEntity;

private:
    void init();
    void handleEvents();
    void update();
    void render();
    void cleanup();
    void handleInput(const b2BodyId &bodyId);

private:
    Player mPlayer {};
    bool mIsRunning {};
    Map mMap {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_PLATFORMER_H_
