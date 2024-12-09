///
/// Includes the Game Class
///

#ifndef INCLUDE_PLATFORMER_PLATFORMER_H_
#define INCLUDE_PLATFORMER_PLATFORMER_H_

#include "box2d/id.h"
#include "entt/entity/fwd.hpp"
#include "utils/Map.h"
#include "Platformer/Physics.h"

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
    bool mIsRunning {};
    Map mMap {};
    Physics mPhysics {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_PLATFORMER_H_
