#include "Player.h"

#include "Platformer/Physics/Physics.h"
#include "PlayerState.h"

#include <SDL_timer.h>
#include <box2d/collision.h>
#include <SDL_rect.h>
#include <box2d/box2d.h>

namespace Platformer
{

b2BodyId Player::playerBody {};

void Player::init()
{
    b2BodyDef playerBodyDef     = b2DefaultBodyDef();
    playerBodyDef.type          = b2_dynamicBody;
    playerBodyDef.position      = (b2Vec2) {7.0f, 8.0f};
    playerBodyDef.fixedRotation = true;
    playerBody = b2CreateBody(Physics::worldId, &playerBodyDef);

    // Player body
    b2Polygon playerBodyBox = b2MakeOffsetBox(
        0.34375, 0.375, {0, -0.125}, b2Rot {1.f, 0.f});  // I did my maths

    // I hate clang-format. The lua formatter is so good it doesn't get in your
    // way. Might be a lil slow but gets the job done. Look at what clang
    // clang-format did to this.

    b2ShapeDef playerShapeDef         = b2DefaultShapeDef();
    playerShapeDef.density            = 1.0f;
    playerShapeDef.friction           = 0.1f;
    playerShapeDef.enableSensorEvents = true;
    b2CreatePolygonShape(playerBody, &playerShapeDef, &playerBodyBox);

    // Foot sensor
    b2Polygon footSensorBox =
        b2MakeOffsetBox(0.32f, 0.1f, {0, -0.9f}, b2Rot {1.f, 0.f});
    b2ShapeDef footSensorShape = b2DefaultShapeDef();
    footSensorShape.isSensor   = true;
    footSensorId =
        b2CreatePolygonShape(playerBody, &footSensorShape, &footSensorBox);

    mPlayerState->init();
}

void Player::update()
{

    // Checking body on ground
    int groundContactCount      = 0;
    b2SensorEvents sensorEvents = b2World_GetSensorEvents(Physics::worldId);

    for (int i = 0; i < sensorEvents.beginCount; ++i)
    {
        const b2SensorBeginTouchEvent *event = &sensorEvents.beginEvents[i];
        if (B2_ID_EQUALS(event->sensorShapeId, footSensorId))
        {
            groundContactCount++;
        }
    }

    for (int i = 0; i < sensorEvents.endCount; ++i)
    {
        const b2SensorEndTouchEvent *event = &sensorEvents.endEvents[i];
        if (B2_ID_EQUALS(event->sensorShapeId, footSensorId))
        {
            groundContactCount--;
        }
    }
    bool isPlayerOnGround = (groundContactCount > 0);
    bool isPlayerOnAir    = (groundContactCount < 0);

    if (isPlayerOnGround)
    {
        inAir = false;
    }

    if (isPlayerOnAir)
    {
        inAir = true;
    }

    mPlayerState->update(inAir);
}

void Player::render() {
    mPlayerState->render();
}

}  // namespace Platformer
