#include "Platformer/Physics.h"

namespace Platformer
{

void Physics::init()
{

    worldDef               = b2DefaultWorldDef();  // The world
    worldDef.gravity       = (b2Vec2) {0.0f, -10.0f};
    worldId                = b2CreateWorld(&worldDef);
    groundBodyDef          = b2DefaultBodyDef();  // The static body ground
    groundBodyDef.position = (b2Vec2) {0.0f, -10.0f};
    groundId               = b2CreateBody(worldId, &groundBodyDef);
    groundBox              = b2MakeBox(100.0f, 10.0f);
    groundShapeDef         = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // The dynamic body(player)
    bodyDef           = b2DefaultBodyDef();
    bodyDef.type      = b2_dynamicBody;
    bodyDef.position  = (b2Vec2) {0.0f, 4.0f};
    bodyId            = b2CreateBody(worldId, &bodyDef);
    dynamicBox        = b2MakeBox(1.0f, 1.0f);
    shapeDef          = b2DefaultShapeDef();
    shapeDef.density  = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void Physics::update() {}

void Physics::close()
{
    b2DestroyWorld(worldId);
}

}  // namespace Platformer
