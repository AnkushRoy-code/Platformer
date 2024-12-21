#ifndef INCLUDE_PLAYER_PLAYER_H_
#define INCLUDE_PLAYER_PLAYER_H_

#include "box2d/box2d.h"
#include "box2d/id.h"
namespace Platformer
{
class Player
{
public:
    static b2BodyId playerBody;
    void init();
    void update();

    void close()
    {
        b2DestroyBody(playerBody);
    }

private:
    bool doubleJumpAble {false};
    bool inAir {false};
    b2ShapeId footSensorId {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLAYER_PLAYER_H_
