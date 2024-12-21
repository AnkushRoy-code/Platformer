#include "Player.h"
#include "Platformer/Physics/Physics.h"
#include "Platformer/Core/KeyState.h"
#include "box2d/collision.h"
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
    b2Polygon playerBodyBox           = b2MakeBox(0.5, 0.5);
    b2ShapeDef playerShapeDef         = b2DefaultShapeDef();
    playerShapeDef.density            = 1.0f;
    playerShapeDef.friction           = 0.1f;
    playerShapeDef.enableSensorEvents = true;
    b2CreatePolygonShape(playerBody, &playerShapeDef, &playerBodyBox);

    // Foot sensor
    b2Polygon footSensorBox =
        b2MakeOffsetBox(0.49f, 0.1f, {0, -0.9f}, b2Rot {1.f, 0.f});
    b2ShapeDef footSensorShape = b2DefaultShapeDef();
    footSensorShape.isSensor   = true;
    footSensorId =
        b2CreatePolygonShape(playerBody, &footSensorShape, &footSensorBox);
}

void Player::update()
{
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
        inAir          = false;
        doubleJumpAble = true;
    }
    if (isPlayerOnAir)
    {
        inAir = true;
    }

    // Handling inputs
    using namespace Platformer::KeyState;

    b2Vec2 vel     = b2Body_GetLinearVelocity(playerBody);
    b2Vec2 gravity = b2World_GetGravity(Physics::worldId);

    if (keyState[SHIFT])
    {
        if (keyState[LEFT] && !keyState[RIGHT])
        {
            if (vel.x > -1)
            {
                b2Body_ApplyForceToCenter(playerBody, b2Vec2 {-50, gravity.y},
                                          true);
            }
            else
            {
                b2Body_ApplyForceToCenter(
                    playerBody, b2Vec2 {vel.x * -10, gravity.y}, true);
            }
        }

        else if (keyState[RIGHT] && !keyState[LEFT])
        {
            if (vel.x < 1)
            {
                b2Body_ApplyForceToCenter(playerBody, b2Vec2 {50, gravity.y},
                                          true);
            }
            else
            {
                b2Body_ApplyForceToCenter(
                    playerBody, b2Vec2 {vel.x * -10, gravity.y}, true);
            }
        }
        else
        {
            b2Body_ApplyForceToCenter(playerBody,
                                      b2Vec2 {vel.x * -10, gravity.y}, true);
        }
    }
    else
    {

        if (keyState[LEFT] && !keyState[RIGHT])
        {
            if (vel.x > -5)
            {
                b2Body_ApplyForceToCenter(playerBody, b2Vec2 {-50, gravity.y},
                                          true);
            }
        }

        if (keyState[RIGHT] && !keyState[LEFT])
        {
            if (vel.x < 5)
            {
                b2Body_ApplyForceToCenter(playerBody, b2Vec2 {50, gravity.y},
                                          true);
            }
        }

        if (keyState[SPACE])
        {
            if (!inAir)
            {
                b2Body_ApplyLinearImpulseToCenter(playerBody, b2Vec2 {0, 7},
                                                  true);
            }
            else if (doubleJumpAble)
            {
                b2Body_ApplyLinearImpulseToCenter(playerBody, b2Vec2 {0, 7},
                                                  true);
                doubleJumpAble = false;
            }
            keyRelease(SPACE);  // Reset key state after handling
        }
    }
}

}  // namespace Platformer
