#include "Player.h"
#include "Platformer/Physics.h"
#include "Platformer/keyState.h"
#include "box2d/collision.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include <box2d/box2d.h>

namespace Platformer
{

b2BodyId Player::playerBody {};

void Player::init()
{
    b2BodyDef bodyDef     = b2DefaultBodyDef();
    bodyDef.type          = b2_dynamicBody;
    bodyDef.position      = (b2Vec2) {5.0f, 4.0f};
    bodyDef.fixedRotation = true;
    playerBody            = b2CreateBody(Physics::worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeRoundedBox(0.4, 0.4, 0.1);
    b2ShapeDef shapeDef  = b2DefaultShapeDef();
    shapeDef.density     = 1.0f;
    shapeDef.friction    = 0.3f;
    b2CreatePolygonShape(playerBody, &shapeDef, &dynamicBox);

    // // Foot sensor
    // b2Vec2 bodyPos          = b2Body_GetLocalCenterOfMass(playerBody);
    // b2Polygon footSensorBox = b2MakeOffsetBox(
    //     0.1f, 0.1f, b2Vec2 {bodyPos.x, bodyPos.y - 0.9f}, b2Rot {0.f, 0.f});
    // b2ShapeDef footSensorShape         = b2DefaultShapeDef();
    // footSensorShape.isSensor           = true;
    // footSensorShape.enableSensorEvents = true;
    // b2CreatePolygonShape(playerBody, &footSensorShape, &footSensorBox);
}

void Player::update()
{
    using namespace Platformer::KeyState;

    // using linearVel
    /* switch (keyState.to_ulong())

    b2Vec2 vel = b2Body_GetLinearVelocity(playerBody);
    {
        case (1 << LEFT):
            vel.x = b2MaxFloat(vel.x - 0.1f, -5.0f);
            b2Body_SetLinearVelocity(playerBody, vel);
            break;

        case (1 << RIGHT):
            vel.x = b2MinFloat(vel.x + 0.1f, 5.0f);
            b2Body_SetLinearVelocity(playerBody, vel);
            break;

        case (1 << SHIFT):
            vel.x *= 0.98;
            b2Body_SetLinearVelocity(playerBody, vel);
            break;

        case (1 << SPACE):
            b2Body_ApplyLinearImpulseToCenter(playerBody, b2Vec2 {vel.x, 1},
                                              true);
            break;
        default:
            break;
    } */

    // Using Force

    b2Vec2 vel     = b2Body_GetLinearVelocity(playerBody);
    b2Vec2 gravity = b2World_GetGravity(Physics::worldId);

    switch (keyState.to_ulong())
    {
        case (1 << LEFT):
            if (vel.x > -5)
            {
                b2Body_ApplyForceToCenter(playerBody, b2Vec2 {-50, gravity.y},
                                          true);
            }
            break;

        case (1 << RIGHT):
            if (vel.x < 5)
                b2Body_ApplyForceToCenter(playerBody, b2Vec2 {50, gravity.y},
                                          true);
            break;

        case (1 << SHIFT):
            b2Body_ApplyForceToCenter(playerBody,
                                      b2Vec2 {vel.x * -10, gravity.y}, true);
            break;

        case (1 << SPACE):
            b2Body_ApplyLinearImpulseToCenter(playerBody, b2Vec2 {0, 7}, true);
            keyRelease(SPACE);

            break;
        default:
            break;
    }

}

/*
 // using lookup table
std::array<std::function<void()>, 7> keyActions = {
    []() { std::cout << "SPACE pressed\n"; },
    []() { std::cout << "RIGHT pressed\n"; },
    []() { std::cout << "LEFT pressed\n"; },
    []() { std::cout << "SHIFT pressed\n"; },
    []() { std::cout << "R_MOUSEBUTTON pressed\n"; },
    []() { std::cout << "L_MOUSEBUTTON pressed\n"; },
    []() { std::cout << "M_MOUSEBUTTON pressed\n"; },
};

void processKey(int key) {
    if (keyState.isKeypressed(key)) {
        keyActions[key]();
    }
}
*/

}  // namespace Platformer
