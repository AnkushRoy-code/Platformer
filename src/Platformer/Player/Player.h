#ifndef INCLUDE_PLAYER_PLAYER_H_
#define INCLUDE_PLAYER_PLAYER_H_

#include "PlayerState.h"
#include "Utils/Components/Component.h"
#include "box2d/box2d.h"
#include "box2d/id.h"
#include <memory>
namespace Platformer
{
class Player
{
public:
    static b2BodyId playerBody;
    void render();
    void init();
    void update();

    void close()
    {
        b2DestroyBody(playerBody);
    }

private:
    bool inAir {false};
    b2ShapeId footSensorId {};
    std::unique_ptr<PlayerState> mPlayerState = std::make_unique<PlayerState>();
};

}  // namespace Platformer

#endif  // INCLUDE_PLAYER_PLAYER_H_
