#include "PlayerState.h"

#include "Player.h"
#include "Platformer/Physics/Physics.h"
#include "Platformer/Core/KeyState.h"

#include <box2d/box2d.h>
#include <box2d/math_functions.h>
#include <iostream>

namespace Platformer
{

void PlayerState::update(bool InAir)
{
    inAir   = InAir;
    vel     = b2Body_GetLinearVelocity(Player::playerBody);
    gravity = b2World_GetGravity(Physics::worldId);

    switch (currentState)
    {
            // clang-format off
        case States::Idling        : updateIdling(); break;
        case States::Walking       : updateWalking(); break;
        case States::Falling       : updateFalling(); break;
        case States::Jumping       : updateJumping(); break;
        case States::DoubleJumping : updateDoubleJumping(); break;
            // clang-format on
    }
}

using namespace Platformer::KeyState;

void applyForce(const b2Vec2 &force)
{
    b2Body_ApplyForceToCenter(Player::playerBody, force, true);
}

void applyImpulse(const b2Vec2 &impulse)
{
    b2Body_ApplyLinearImpulseToCenter(Player::playerBody, impulse, true);
}

void PlayerState::updateMovement()
{
    float maxSpeed {5};

    if (keyState[LEFT] && !keyState[RIGHT])
    {
        if (vel.x > -maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {-force, gravity.y}, true);
        }
    }

    if (keyState[RIGHT] && !keyState[LEFT])
    {
        if (vel.x < maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {force, gravity.y}, true);
        }
    }
}

void PlayerState::updateIdling()
{
    if (keyState[LEFT] || keyState[RIGHT])
    {
        currentState = States::Walking;
    }
    if (keyState[SPACE])
    {
        currentState = States::Jumping;
    }
}

void PlayerState::updateWalking()
{
    updateMovement();
    if (!keyState[LEFT] && !keyState[RIGHT])
    {
        currentState = States::Idling;
    }
    if (keyState[SPACE])
    {
        currentState = States::Jumping;
    }
}

void PlayerState::updateFalling()
{
    updateMovement();
    if (!inAir)
    {
        currentState   = States::Idling;
        doubleJumpAble = true;
    }

    if (keyState[SPACE] && doubleJumpAble)
    {
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        currentState = States::DoubleJumping;
        keyRelease(SPACE);
        doubleJumpAble = false;
    }
}

void PlayerState::updateJumping()
{
    updateMovement();
    if (vel.y < 0)
    {
        currentState = States::Falling;
    }
    if (keyState[SPACE] && doubleJumpAble)
    {
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        currentState = States::DoubleJumping;
        keyRelease(SPACE);
        doubleJumpAble = false;
    }
}

void PlayerState::updateDoubleJumping()
{
    updateMovement();
    if (vel.y < 0)
    {
        currentState = States::Falling;
    }

    else if (keyState[SPACE])
    {
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        currentState = States::Jumping;
        keyRelease(SPACE);
    }
}

}  // namespace Platformer
