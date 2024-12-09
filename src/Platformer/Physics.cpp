#include "Platformer/Physics.h"

namespace Platformer
{

b2WorldId Physics::worldId {};

void initGround()
{
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position  = (b2Vec2) {0.0f, -10.0f};

    b2BodyId groundId   = b2CreateBody(Physics::worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);

    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
}

void Physics::init()
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity    = (b2Vec2) {0.0f, -9.807f};
    worldId             = b2CreateWorld(&worldDef);
}

void Physics::update()
{
    constexpr float timeStep   = 1.0f / 60.0f;
    constexpr int subStepCount = 4;
    b2World_Step(worldId, timeStep, subStepCount);
}

void Physics::close()
{
    b2DestroyWorld(worldId);
}

}  // namespace Platformer
