#include "PlayerState.h"

#include "Player.h"
#include "Platformer/Physics/Physics.h"
#include "Platformer/Core/KeyState.h"
#include "Utils/Components/Animation.h"

#include <SDL_rect.h>
#include <box2d/box2d.h>
#include <box2d/math_functions.h>

namespace Platformer
{

void PlayerState::init()
{
    mAnimations.addAnimation("res/images/Player/Animations/Idle.png", 1, 1, 11,
                             1000 / 12, States::Idling);

    mAnimations.init();
}

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

void PlayerState::render()
{

    b2Vec2 pos = b2Body_GetPosition(Player::playerBody);

    SDL_FRect rect = {pos.x - 0.5f, pos.y - 0.5f, 1, 1};

    mAnimations.playAnimation(States::Idling, rect);
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

    else if (keyState[RIGHT] && !keyState[LEFT])
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
    // mAnimations.playAnimation(States::Idling)
    if (keyState[LEFT] || keyState[RIGHT])
    {
        currentState = States::Walking;
    }
    else if (keyState[SPACE])
    {
        currentState = States::Jumping;
    }
}

void PlayerState::updateWalking()
{
    // Same as updateMovement
    float maxSpeed {5};

    if (keyState[LEFT] && !keyState[RIGHT])
    {
        if (vel.x > -maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {-force, gravity.y}, true);
        }
    }

    else if (keyState[RIGHT] && !keyState[LEFT])
    {
        if (vel.x < maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {force, gravity.y}, true);
        }
    }

    else if (!keyState[LEFT] && !keyState[RIGHT])
    {
        currentState = States::Idling;
    }
    else if (keyState[SPACE])
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

    else if (keyState[SPACE] && doubleJumpAble)
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

    else if (keyState[SPACE] && doubleJumpAble)
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
