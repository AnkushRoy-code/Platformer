#ifndef INCLUDE_PLAYER_PLAYER_H_
#define INCLUDE_PLAYER_PLAYER_H_

#include "PlayerState.h"
#include "box2d/box2d.h"
#include "box2d/id.h"
#include "entt/entity/fwd.hpp"
#include <memory>
namespace Platformer
{
class Player
{
public:
    static b2BodyId playerBody;
    static void render(entt::registry &reg);
    void init();
    void update();

    void close()
    {
        b2DestroyBody(playerBody);
    }

private:
    // bool doubleJumpAble {false};
    bool inAir {false};
    // float maxSpeed {5};
    b2ShapeId footSensorId {};
    std::unique_ptr<PlayerState> state = std::make_unique<PlayerState>();
};

}  // namespace Platformer

#endif  // INCLUDE_PLAYER_PLAYER_H_
