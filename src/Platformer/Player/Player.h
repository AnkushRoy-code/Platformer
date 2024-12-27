#ifndef INCLUDE_PLAYER_PLAYER_H_
#define INCLUDE_PLAYER_PLAYER_H_

#include "box2d/box2d.h"
#include "box2d/id.h"
#include "entt/entity/fwd.hpp"
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
    bool doubleJumpAble {false};
    bool inAir {false};
    float maxSpeed {5};
    b2ShapeId footSensorId {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLAYER_PLAYER_H_
