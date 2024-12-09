#ifndef INCLUDE_PLATFORMER_PHYSICS_H_
#define INCLUDE_PLATFORMER_PHYSICS_H_

#include "box2d/box2d.h"

namespace Platformer
{

class Physics
{
public:
    void init();
    void close();
    void update();

private:
    b2WorldDef worldDef {};
    b2WorldId worldId {};
    b2BodyDef groundBodyDef {};
    b2BodyId groundId {};
    b2Polygon groundBox {};
    b2ShapeDef groundShapeDef {};
    b2BodyDef bodyDef {};
    b2BodyId bodyId {};
    b2Polygon dynamicBox {};
    b2ShapeDef shapeDef {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_PHYSICS_H_
