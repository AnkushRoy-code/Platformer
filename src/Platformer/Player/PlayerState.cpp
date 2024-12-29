#include "PlayerState.h"

#include "Platformer/Core/Music.h"
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
    mAnimations.addAnimation("res/Images/Player/Animations/Idle.png", 1, 1, 11,
                             1000 / 12, States::IDLING);

    mAnimations.addAnimation("res/Images/Player/Animations/Run.png", 1, 1, 12,
                             1000 / 20, States::WALKING);

    mAnimations.addAnimation("res/Images/Player/Animations/Fall.png", 1, 1,
                             States::FALLING);

    mAnimations.addAnimation("res/Images/Player/Animations/Jump.png", 1, 1,
                             States::JUMPING);

    mAnimations.addAnimation("res/Images/Player/Animations/DoubleJump.png", 1,
                             1, 6, 1000 / 20, States::DOUBLE_JUMPING);

    mAnimations.init();

    mSFXes.addSFX(SFX::JUMP, "res/Sounds/SFX/Player/Jump.mp3");
    mSFXes.addSFX(SFX::DJUMP, "res/Sounds/SFX/Player/Jump.mp3");
    mSFXes.addSFX(SFX::RUN, "res/Sounds/SFX/Player/Run.mp3");
}

void PlayerState::update(bool InAir)
{
    inAir   = InAir;
    vel     = b2Body_GetLinearVelocity(Player::playerBody);
    gravity = b2World_GetGravity(Physics::worldId);

    switch (currentState)
    {
            // clang-format off
        case States::IDLING        : updateIdling(); break;
        case States::WALKING       : updateWalking(); break;
        case States::FALLING       : updateFalling(); break;
        case States::JUMPING       : updateJumping(); break;
        case States::DOUBLE_JUMPING : updateDoubleJumping(); break;
            // clang-format on
    }
}

void PlayerState::render()
{

    b2Vec2 pos = b2Body_GetPosition(Player::playerBody);

    SDL_FRect rect = {pos.x - 0.5f, pos.y - 0.5f, 1, 1};

    mAnimations.playAnimation(currentState, rect, dirLeft);
}

void PlayerState::close()
{
    mSFXes.close();
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
        dirLeft = false;
        if (vel.x > -maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {-force, gravity.y}, true);
        }
    }

    else if (keyState[RIGHT] && !keyState[LEFT])
    {
        dirLeft = true;
        if (vel.x < maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {force, gravity.y}, true);
        }
    }
}

void PlayerState::fallingCondition()
{
    if (vel.y < -0.13)
    {
        currentState = States::FALLING;
    }
}

void PlayerState::updateIdling()
{
    // mAnimations.playAnimation(States::Idling)
    if ((keyState[LEFT] || keyState[RIGHT])
        && !(keyState[LEFT] && keyState[RIGHT]))
    {
        currentState = States::WALKING;
    }

    if (keyState[SPACE])
    {
        currentState = States::JUMPING;
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        keyRelease(SPACE);
    }
    fallingCondition();
}

void PlayerState::updateWalking()
{
    mSFXes.playSFX(SFX::RUN);
    // Same as updateMovement
    float maxSpeed {5};

    if (keyState[LEFT] && !keyState[RIGHT])
    {
        dirLeft = false;
        if (vel.x > -maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {-force, gravity.y}, true);
        }
    }

    else if (keyState[RIGHT] && !keyState[LEFT])
    {
        dirLeft = true;
        if (vel.x < maxSpeed)
        {
            b2Body_ApplyForceToCenter(Player::playerBody,
                                      b2Vec2 {force, gravity.y}, true);
        }
    }

    else if ((!keyState[LEFT] && !keyState[RIGHT])
             || (keyState[LEFT] && keyState[RIGHT]))
    {
        currentState = States::IDLING;
        mSFXes.stopSFX(SFX::RUN);
    }

    if (keyState[SPACE])
    {
        currentState = States::JUMPING;
        mSFXes.stopSFX(SFX::RUN);
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        keyRelease(SPACE);
    }

    fallingCondition();
}

void PlayerState::updateFalling()
{
    updateMovement();
    if (!inAir)
    {
        currentState   = States::IDLING;
        doubleJumpAble = true;
    }

    else if (keyState[SPACE] && doubleJumpAble)
    {
        b2Body_SetLinearVelocity(Player::playerBody, b2Vec2 {vel.x, 0});
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        currentState = States::DOUBLE_JUMPING;
        keyRelease(SPACE);
        doubleJumpAble = false;
    }

    else if (vel.y == 0)
    {
        currentState = States::IDLING;
    }
}

void PlayerState::updateJumping()
{
    mSFXes.playSFX(SFX::JUMP);
    updateMovement();

    // same as fallingCondition();
    if (vel.y < 0)
    {
        currentState = States::FALLING;
    }

    else if (keyState[SPACE] && doubleJumpAble)
    {
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        currentState = States::DOUBLE_JUMPING;
        keyRelease(SPACE);
        doubleJumpAble = false;
    }
}

void PlayerState::updateDoubleJumping()
{
    mSFXes.playSFX(SFX::DJUMP);
    updateMovement();

    // same as fallingCondition();
    if (vel.y < 0)
    {
        currentState = States::FALLING;
    }

    else if (keyState[SPACE])
    {
        b2Body_ApplyLinearImpulseToCenter(Player::playerBody, b2Vec2 {0, 4.5},
                                          true);
        currentState = States::JUMPING;
        keyRelease(SPACE);
    }
}

}  // namespace Platformer
