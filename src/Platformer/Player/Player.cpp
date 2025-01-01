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

    // b2Polygon playerBodyBoxRound = // round box also solves the problem of
    // // stuck in the corner of ground but does something weird with my inAir
    // // detection so no
    //  
    //     b2MakeOffsetRoundedBox(0.34375, 0.375, {0, -0.125}, b2Rot {1.f, 0.f},
    //                            0.05f);

    // I hate clang-format. The lua formatter is so good it doesn't get in your
    // way. Might be a lil slow but gets the job done. Look at what clang
    // clang-format did to this.

    // b2Capsule capsule;
    // // THey are good but make new problems and I and exams
    // // are really near now. I shouldn't do this
    // capsule.center1 = (b2Vec2) {0.0f, -0.125f};
    // capsule.center2 = (b2Vec2) {0.0f, -0.0625f};
    // capsule.radius  = 0.34375f;

    b2ShapeDef playerShapeDef         = b2DefaultShapeDef();
    playerShapeDef.friction           = 0.2f;
    playerShapeDef.enableSensorEvents = true;
    b2CreatePolygonShape(playerBody, &playerShapeDef, &playerBodyBox);
    // b2CreatePolygonShape(playerBody, &playerShapeDef, &playerBodyBoxRound);
    // b2CreateCapsuleShape(playerBody, &playerShapeDef, &capsule);

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

void Player::render()
{
    mPlayerState->render();
}

}  // namespace Platformer
